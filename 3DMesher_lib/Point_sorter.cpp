#include "Point_sorter.h"


bool xComparator(const Point p1,const Point p2){
    return (p1.x() < p2.x());
}

bool yComparator(const Point p1,const Point p2){
    return (p1.y()<p2.y());
}

bool zComparator(const Point p1,const Point p2){
    return (p1.z()<p2.z());
}

//template<typename Point>
void Point_sorter::clockwiseSort(std::vector<Point> &pointsToSort) {
    //std::vector<Point> pointsSorted;
    iterator vector_it = pointsToSort.begin(),vector_end_it = pointsToSort.end();
   // std::stable_sort(vector_it,vector_end_it, xComparator());

    Point p1, p2, p3, p4;
    std::sort(vector_it, vector_end_it, zComparator);
    //quicksortZ(vector_it, vector_end_it);
    //quicksort(vector_it, vector_end_it);

//    p1= pointsToSort.at(0);
//    p2= pointsToSort.at(1);
//    p3= pointsToSort.at(2);
//    p4= pointsToSort.at(3);


    std::vector<iterator> zGroups_it;
    std::vector<iterator> yGroups_it;
    groupByZ(pointsToSort, zGroups_it, vector_it, vector_end_it);
    FT j = zGroups_it.size();
    iterator2 z_it = zGroups_it.begin(), z_it_end = zGroups_it.end();
    while (z_it != z_it_end)
    {
        iterator it = *z_it;
        z_it++;
        iterator it_end;
        if(z_it != z_it_end) {
            it_end = *z_it;
        }
        else{
            it_end = vector_end_it;
        }
       // quicksortY(it, it_end);
        //quicksort(it, it_end);
        std::sort(it, it_end, yComparator);
////        p1= pointsToSort.at(0);
////        p2= pointsToSort.at(1);
////        p3= pointsToSort.at(2);
////        p4= pointsToSort.at(3);
//
//
        groupByY(pointsToSort, yGroups_it, it, it_end);
        FT i = yGroups_it.size();
        iterator2 y_it = yGroups_it.begin(), y_it_end = yGroups_it.end();
        while (y_it != y_it_end) {
            iterator it2 = *y_it;
            y_it++;
            iterator it2_end;
            if(y_it != y_it_end) {
                it2_end = *y_it;
            }
            else{
                if(it2_end.base() != NULL)
                {
                    it2_end = it_end;
                }
                else{
                    it2_end = vector_end_it;
                }
            }
            //quicksortX(it2, it2_end);
            std::sort(it2, it2_end, xComparator);
//
////            p1= pointsToSort.at(0);
////            p2= pointsToSort.at(1);
////            p3= pointsToSort.at(2);
////            p4= pointsToSort.at(3);
//
//            std::vector<iterator> xGroups_it;
        }
    }
//    std::vector<iterator> xGroups_it;
}

//template<typename Point, typename Point>
void Point_sorter::groupByZ(std::vector<Point> &vectorToGroup, std::vector<iterator> &zGroupIterator, iterator it,
                            iterator it_end) {
    iterator z_iterator = it, z_iterator_end = it_end;
    //iterator z_iterator = vectorToGroup.begin(), z_iterator_end = vectorToGroup.end();
    FT z_coordinate_used_for_group = (*z_iterator).z();
    zGroupIterator.emplace_back(z_iterator);
    while(z_iterator != z_iterator_end){
        FT z_value = (*z_iterator).z();
        if( z_value != z_coordinate_used_for_group) // z coordinate of the point
        {
            zGroupIterator.emplace_back(z_iterator);
            z_coordinate_used_for_group = z_value;
        } else
            z_iterator++;

    }

}

//
//void Point_sorter::quicksort(iterator vector_it, iterator vector_end_it, iterator (*fun)(iterator,iterator)) {
//
//    vector_end_it--; //it must be iterator to the last element
//    if(vector_it < vector_end_it) {
//        iterator pivotIterator = partition(vector_it, vector_end_it);
//        quicksort(vector_it, pivotIterator - 1);
//        quicksort(pivotIterator, vector_end_it);
//    }
//}

//void Point_sorter::quicksort(iterator vector_it, iterator vector_end_it) {
//
//    vector_end_it--; //it must be iterator to the last element
//    if(vector_it < vector_end_it) {
//        iterator pivotIterator = partition(vector_it, vector_end_it);
//        quicksort(vector_it, pivotIterator - 1);
//        quicksort(pivotIterator, vector_end_it);
//    }
//}

void Point_sorter::quicksortZ(iterator vector_it, iterator vector_end_it) {

    vector_end_it--; //it must be iterator to the last element
    if(vector_it < vector_end_it) {
        iterator pivotIterator = zPartition(vector_it, vector_end_it);
        quicksortZ(vector_it, pivotIterator);
        //quicksortZ(vector_it, pivotIterator - 1);
        quicksortZ(pivotIterator++, vector_end_it);
    }
}

void Point_sorter::quicksortY(iterator vector_it, iterator vector_end_it) {

    vector_end_it--; //it must be iterator to the last element
    if(vector_it < vector_end_it) {
        iterator pivotIterator = yPartition(vector_it, vector_end_it);
        //quicksortY(vector_it, pivotIterator - 1);
       // quicksortY(pivotIterator, vector_end_it);
        quicksortY(vector_it, pivotIterator);
        quicksortY(pivotIterator++, vector_end_it);

    }
}

void Point_sorter::quicksortX(iterator vector_it, iterator vector_end_it) {

    vector_end_it--; //it must be iterator to the last element
    if(vector_it < vector_end_it) {
        iterator pivotIterator = xPartition(vector_it, vector_end_it);
        //quicksortX(vector_it, pivotIterator - 1);
        quicksortX(vector_it, pivotIterator);
        quicksortX(pivotIterator++, vector_end_it);
    }
}

void Point_sorter::quicksort(iterator vector_it, iterator vector_end_it) {

    vector_end_it--; //it must be iterator to the last element
    if(vector_it < vector_end_it) {
        iterator pivotIterator = partition(vector_it, vector_end_it);
        //quicksort(vector_it, pivotIterator - 1);
        quicksort(vector_it, pivotIterator);
        quicksort(pivotIterator, vector_end_it);
    }
}

iterator Point_sorter::partition(iterator vector_it, iterator vector_end_it) {
    iterator pivotIterator = vector_it + (vector_end_it - vector_it) / 2;
    Point pivotValue = *pivotIterator;
    iterator i = vector_it, j = vector_end_it;
    Point temp;
    while(i <= j) {

        while((*i).z() < pivotValue.z()) { //*i is the point pointed by i
            i++;
        }
        while((*j).z() > pivotValue.z()) {
            j--;
        }
        if(i <= j) {
            temp = *i;
            *i = *j;
            *j = temp;
            i++;
            j--;
        }
    }
    return i;
}

iterator Point_sorter::zPartition(iterator vector_it, iterator vector_end_it) {
    iterator pivotIterator = vector_it + (vector_end_it - vector_it) / 2;
    Point pivotValue = *pivotIterator;
    iterator i = vector_it, j = vector_end_it;
    Point temp;
    while(i <= j) {

        while((*i).z() < pivotValue.z()) { //*i is the point pointed by i
            i++;
        }
        while((*j).z() > pivotValue.z()) {
            j--;
        }
        if(i <= j) {
            temp = *i;
            *i = *j;
            *j = temp;
            i++;
            j--;
        }
    }
    return i;
}

iterator Point_sorter::xPartition(iterator vector_it, iterator vector_end_it) {

    iterator pivotIterator = vector_it + (vector_end_it - vector_it) / 2;
    Point pivotValue = *pivotIterator;
    iterator i = vector_it, j = vector_end_it;
    Point temp;
    while(i <= j) {

        while((*i).x() < pivotValue.x()) { //*i is the point pointed by i
            i++;
        }
        while((*j).x() > pivotValue.x()) {
            j--;
        }
        if(i <= j) {
            temp = *i;
            *i = *j;
            *j = temp;
            i++;
            j--;
        }
    }
    return i;
}

iterator Point_sorter::yPartition(iterator vector_it, iterator vector_end_it) {
    iterator pivotIterator = vector_it + (vector_end_it - vector_it) / 2;
    Point pivotValue = *pivotIterator;
    iterator i = vector_it, j = vector_end_it;
    Point temp;
    while(i <= j) {

        while((*i).y() < pivotValue.y()) { //*i is the point pointed by i
            i++;
        }
        while((*j).y() > pivotValue.y()) {
            j--;
        }
        if(i <= j) {
            temp = *i;
            *i = *j;
            *j = temp;
            i++;
            j--;
        }
    }
    return i;
}



//template<typename Point, typename Point>
void Point_sorter::groupByY(std::vector<Point> &vectorToGroup, std::vector<iterator> &yGroupIterator, iterator it,
                            iterator it_end) {

    //iterator y_iterator = vectorToGroup.begin(), y_iterator_end = vectorToGroup.end();
    iterator y_iterator = it, y_iterator_end = it_end;
    FT y_coordinate_used_for_group = (*y_iterator).y();
    yGroupIterator.emplace_back(y_iterator);
    while(y_iterator != y_iterator_end){
        FT y_value =(*y_iterator).y();
        if( y_value != y_coordinate_used_for_group) // y coordinate of the point
        {
            yGroupIterator.emplace_back(y_iterator);
            y_coordinate_used_for_group = y_value;
        }else
            y_iterator++;
    }
}
