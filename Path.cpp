#include "Path.h"
#include "algo.h"
int map_size;
Node space_map[999][999];
vector<Node> my_path;
vector<Point*> general_point;
vector<Point*> normal_point;
vector<Point*> warp_point;
vector<ShapeTwoD*> normal_shape;
vector<ShapeTwoD*> warp_shape;

bool cmp_point(Point* a, Point* b);
bool cmp_point2(Point* a, Point* b);
bool check_neighbor(Point* a);
void astar(Node start, Node end);
int GetDistance(Node a, Node b);
Node get_warp_in(Node a) ;
Node get_warp_out(Node a) ;
vector <Node> GetNeighbor(Node node, int width, int height);
void Trace(int x1, int y1, int x2, int y2, int width, int height);
void Render();
bool FindElement(vector<Node> node_list, Node element);

//Main function
void Path(vector <ShapeTwoD*> my_shape) {
    //Generate space map
    for(int i=0; i<my_shape.size(); i++) {
        vector<Point*> a = my_shape[i]->getList();
        general_point.insert(general_point.end(), a.begin(), a.end());
        if(my_shape[i]->GetContainsWarpSpace()) {
            warp_shape.push_back(my_shape[i]);
            warp_point.insert(warp_point.end(), a.begin(), a.end());
        } else {
            normal_shape.push_back(my_shape[i]);
            normal_point.insert(normal_point.end(), a.begin(), a.end());
        }
    }
    
    sort(general_point.begin(), general_point.end(), cmp_point);
    map_size = general_point[general_point.size() - 1]->x + 2;
    sort(general_point.begin(), general_point.end(), cmp_point2);
    int size_y = general_point[general_point.size() - 1]->y + 2;
    if(size_y > map_size) {
        map_size = size_y;
    }

    for(int i=0; i<map_size; i++) {
        for(int j=0; j<map_size; j++) {
            space_map[i][j].x = i;
            space_map[i][j].y = j;
            space_map[i][j].walkable = true;
            space_map[i][j].iswrap = false;
            space_map[i][j].gcost = 0;
            space_map[i][j].hcost = 0;
            space_map[i][j].visited = false;
        }
    }

    for(int i=0; i<normal_point.size(); i++) {
        space_map[normal_point[i]->x][normal_point[i]->y].walkable = false;
    }

    for(int i=0; i<warp_point.size(); i++) {
        space_map[warp_point[i]->x][warp_point[i]->y].iswrap = true;
    }


    //Find path
    Node current_loc = space_map[0][0];
    Node end_loc = space_map[map_size - 1][map_size - 1];

    while(current_loc.x != end_loc.x || current_loc.y != end_loc.y) {

        //Get warp in and warp out location
        Node warp_into = get_warp_in(current_loc);
        Node warp_out = get_warp_out(warp_into);
        vector<Node> out_neighbor = GetNeighbor(warp_out, map_size, map_size);
            vector<int> my_distance;
            for(int i=0; i<out_neighbor.size(); i++) {
                if(!space_map[out_neighbor[i].x][out_neighbor[i].y].walkable || space_map[out_neighbor[i].x][out_neighbor[i].y].iswrap){
                    my_distance.push_back(999);
                } else {
                    my_distance.push_back(GetDistance(space_map[out_neighbor[i].x][out_neighbor[i].y], end_loc));
               }
           }

            int index = distance(begin(my_distance), min_element(begin(my_distance), end(my_distance)));
            warp_out.x = out_neighbor[index].x;
            warp_out.y = out_neighbor[index].y;
        
        //Main logic
        if(GetDistance(current_loc, end_loc) < GetDistance(current_loc, warp_into) + GetDistance(warp_out, end_loc)) {
            astar(current_loc, end_loc);
            break;
        } else {
            astar(current_loc, warp_into);
            current_loc.x = warp_out.x;
            current_loc.y = warp_out.y;
        }
    }

    //Print path
    Render();
    Freeze();
    my_path.clear();
}

//Compare point by x then y
bool cmp_point(Point* a, Point* b) {
    if(a->x == b->x) {
        return a->y < b->y;
    } else {
        return a->x < b->x;
    }
}

//Compare point by y then x
bool cmp_point2(Point* a, Point* b) {
    if(a->y == b->y) {
        return a->x < b->x;
    } else {
        return a->y < b->y;
    }
}

//A* path finding
void astar(Node start_node, Node end_node) {
    vector<Node> open_node;
    vector<Node> closed_node;
    open_node.push_back(start_node);
    while(open_node.size() > 0) {
        int pos = 0;
        Node current_node = open_node[0];
        for(int i=1; i<open_node.size(); i++) {

            if(open_node[i].getFcost() < current_node.getFcost() || 
            open_node[i].getFcost() == current_node.getFcost()) {

                if(open_node[i].hcost < current_node.hcost) {
                    current_node = open_node[i];
                    pos = i;
                }
            }
        }

        open_node.erase(open_node.begin() + pos);
        closed_node.push_back(current_node);
        current_node.visited = true;

        if(current_node.x == end_node.x && current_node.y == end_node.y) {
            Trace(start_node.x, start_node.y, end_node.x, end_node.y, map_size, map_size);
            break;
        }
        vector<Node> neighbor;
        neighbor = GetNeighbor(current_node, map_size, map_size);
        for(int i=0; i<neighbor.size(); i++) {
            if(!neighbor[i].walkable || FindElement(closed_node, neighbor[i]) || neighbor[i].visited) continue;

            int cost_to_neighbor = current_node.gcost + GetDistance(current_node, neighbor[i]);

            if(cost_to_neighbor < neighbor[i].gcost || !FindElement(open_node, neighbor[i])) {
                neighbor[i].gcost = cost_to_neighbor;
                neighbor[i].hcost = GetDistance(neighbor[i], end_node);
                space_map[neighbor[i].x][neighbor[i].y].parent.push_back(current_node.x);
                space_map[neighbor[i].x][neighbor[i].y].parent.push_back(current_node.y);
                if(!FindElement(open_node, neighbor[i])) open_node.push_back(neighbor[i]);
            }
        }
    }

}

//Get distance between two node
int GetDistance(Node a, Node b) {
    int distanceX = abs(a.x - b.x);
    int distanceY = abs(a.y - b.y);

    if(distanceX > distanceY) {
        return 14 * distanceY + 10 * (distanceX - distanceY);
    } else {
        return 14 * distanceX + 10 * (distanceY - distanceX);
    }
}

//Get surrounding node
vector <Node> GetNeighbor(Node node, int width, int height) {
    vector<Node> result;
    for(int x= - 1; x<=1; x++) {
        for(int y= -1; y<=1; y++) {
            if(x ==0 && y ==0) {
                continue;
            }
            int checkx = node.x + x;
            int checky = node.y + y;
            if(checkx >=0 && checkx < height && checky >=0 && checky < width) {
                result.push_back(space_map[checkx][checky]);
            }
        }
    }
    return result;
}

//Find a node element in a vector
bool FindElement(vector<Node> node_list, Node element) {
    for(int i=0; i<node_list.size(); i++) {
        if(node_list[i].x == element.x && node_list[i].y == element.y) {
            return true;
        }
    }
    return false;
}

//Get path info
void Trace(int x1, int y1, int x2, int y2, int width, int height) {
    vector<Node> pth;
    while(x2 != x1 || y2 != y1) {
        pth.push_back(space_map[x2][y2]);
        int newx = space_map[x2][y2].parent[0];
        int newy = space_map[x2][y2].parent[1];
        x2 = newx;
        y2 = newy;
        if (x2 == x1 || y2 == y1) {
            pth.push_back(space_map[x2][y2]);
        }  
    }
    reverse(pth.begin(), pth.end());
    my_path.insert(my_path.end(), pth.begin(), pth.end());
}

//Get nearest warp in
Node get_warp_in(Node a) {
    vector<Point*> point_conatiner;
    vector<Point*> container_shape;
    vector<int> my_distance;
    if(warp_shape.size() != 0){
        for(int i=0; i<warp_shape.size(); i++){
            container_shape = warp_shape[i]->getList();
            for(int j=0; j<container_shape.size(); j++) {
                point_conatiner.push_back(container_shape[j]);
                if((!space_map[container_shape[j]->x][container_shape[j]->y].walkable) || (container_shape[j]->y < a.y) || (container_shape[j]->y == a.y && container_shape[j]->x < a.x)) {
                    my_distance.push_back(999);
                } else {
                    my_distance.push_back(GetDistance(a, space_map[container_shape[j]->x][container_shape[j]->y]));
                }
            }
        }
        int index = distance(begin(my_distance), min_element(begin(my_distance), end(my_distance)));
        return space_map[point_conatiner[index]->x][point_conatiner[index]->y];
    } else {
        return space_map[0][0];
    }
}

//Get warp out location that nearest to exit
Node get_warp_out(Node a) {
    int x = 0;
    int y = 0;
    vector<Point*> container_shape;
    if(warp_shape.size() != 0){
        for(int i=0; i<warp_shape.size(); i++){
            container_shape = warp_shape[i]->getList();
            vector<Point*> point_conatiner;
            for(int j=0; j<container_shape.size(); j++) {
                if(check_neighbor(container_shape[j])) {
                    point_conatiner.push_back(container_shape[j]);
                }
            }
            for(int j=0; j<point_conatiner.size(); j++) {
                if(a.x == point_conatiner[j]->x && a.y == point_conatiner[j]->y) {
                    sort(point_conatiner.begin(), point_conatiner.end(), cmp_point2);
                    x = point_conatiner[point_conatiner.size()-1]->x;
                    y = point_conatiner[point_conatiner.size()-1]->y;
                }
            }
        }
    }
    return space_map[x][y];
}

//Check if a node is bad (surround by normal shape)
bool check_neighbor(Point* a) {
    vector<Node> my_neighbor = GetNeighbor(space_map[a->x][a->y], map_size, map_size);
    for(int i=0; i<my_neighbor.size(); i++) {
        if(my_neighbor[i].walkable){
            return true;
        }
    }
    return false;
}

//Print space map
void Render() {
    cout << endl;
    cout << "[Find path to exit]" << endl;
	
	for (int i=map_size - 1; i>= 0; i--) {
        for (int j=0; j<map_size; j++) {
            if(i == 0 && j == 0){
                cout << "S ";
            } else if (i == map_size - 1 && j == map_size - 1){
                cout << "E ";
            } else if(!space_map[j][i].walkable) {
                cout << "N ";
            } else if(space_map[j][i].iswrap) {
                cout << "W ";
            } else if(FindElement(my_path, space_map[j][i])) {
                cout << ". ";
            } else {
                cout << "  ";
            }
        }
        cout << endl;
    }
}