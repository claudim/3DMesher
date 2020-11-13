#include "Point_sorter.h"


bool xComparator(const Point p1,const Point p2){
    return (p1.x() < p2.x());
}

bool yComparator(const Point p1,const Point p2){
    return (p1.y() < p2.y());
}

bool zComparator(const Point p1,const Point p2){
    return (p1.z() < p2.z());
}

//template<typename Point>
void Point_sorter::sortByZYX(std::vector<Point> &pointsToSort) {
    iterator vector_it = pointsToSort.begin(),vector_end_it = pointsToSort.end();
    // sort the z coordinates
    std::sort(vector_it, vector_end_it, zComparator);

    std::vector<iterator> zGroups_it;
    std::vector<iterator> yGroups_it;
    groupByZ(pointsToSort, zGroups_it, vector_it, vector_end_it);
    // sort the y coordinates
    for(iterator2 z_it = zGroups_it.begin(),z_it2 = ++zGroups_it.begin(), z_it_end = zGroups_it.end(); z_it!= z_it_end; ++z_it, ++z_it2){
        if(z_it2 != z_it_end) {
            std::sort(*z_it, *z_it2, yComparator);
            groupByY(pointsToSort, yGroups_it, *z_it, *z_it2);
        }
        else{
            std::sort(*z_it, pointsToSort.end(), yComparator);
            groupByY(pointsToSort, yGroups_it, *z_it, pointsToSort.end());
        }
    }
    // sort the x coordinates
    for(iterator2 y_it = yGroups_it.begin(),y_it2 = ++yGroups_it.begin(), y_it_end = yGroups_it.end(); y_it!= y_it_end; ++y_it, ++y_it2){
        if(y_it2 != y_it_end) {
            std::sort(*y_it, *y_it2, xComparator);
        }
        else{
            std::sort(*y_it, pointsToSort.end(), xComparator);
        }
    }
}

//template<typename Point, typename Point>
void Point_sorter::groupByZ(std::vector<Point> &vectorToGroup, std::vector<iterator> &zGroupIterator, iterator it,
                            iterator it_end) {
    iterator z_iterator = it, z_iterator_end = it_end;
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



//template<typename Point, typename Point>
void Point_sorter::groupByY(std::vector<Point> &vectorToGroup, std::vector<iterator> &yGroupIterator, iterator it,
                            iterator it_end) {
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

////template<typename Point, typename Point>
//void Point_sorter::sort_southest_points_facet(std::vector<Point> &points, std::vector<Point> &southestFacetPoints) {
//    sortByZYX(points);
//    if(points.size() >= 4)
//    {
//        for(int i = 0; i < 4; i++)
//        {
//            southestFacetPoints.emplace_back(points[i]);
//        }
//        // exchange the last point with the penultimate one
//        Point supportVariable = southestFacetPoints[3];
//        southestFacetPoints[3] = southestFacetPoints[2];
//        southestFacetPoints[2] = supportVariable;
//
//        //if the first point has x-coordinate less than the fourth, then make a rotation of the points
//        if (southestFacetPoints[0].x() > southestFacetPoints[3].x())
//        {
//            std::rotate(southestFacetPoints.begin(),
//                        southestFacetPoints.end()-1, // this will be the new first element
//                        southestFacetPoints.end());
//        }
//    }
//}

void Point_sorter::sort_southest_points_facet(std::vector<Point> &points, std::vector<Point> &southestFacetPoints) {
    //sortByZYX(points);
    std::sort(points.begin(), points.end(), zComparator);
    if(points.size() >= 4){
        for(int i = 0; i < 4; i++)
        {
            southestFacetPoints.emplace_back(points[i]);
        }
        // sort by Y
        iterator vector_it = southestFacetPoints.begin(),vector_end_it = southestFacetPoints.end();
        std::sort(vector_it, vector_end_it, yComparator);

        // group by Y
        std::vector<iterator> yGroups_it;
        groupByY(southestFacetPoints, yGroups_it, vector_it, vector_end_it);

        // sort the x coordinates
        for(iterator2 y_it = yGroups_it.begin(),y_it2 = ++yGroups_it.begin(), y_it_end = yGroups_it.end(); y_it!= y_it_end; ++y_it, ++y_it2){
            if(y_it2 != y_it_end) {
                std::sort(*y_it, *y_it2, xComparator);
            }
            else{
                std::sort(*y_it, southestFacetPoints.end(), xComparator);
            }
        }


        // sort to obtain the northest points facet order
        if(southestFacetPoints[0].x() > southestFacetPoints[1].x()){
            Point supportVariable = southestFacetPoints[0];
            southestFacetPoints[0] = southestFacetPoints[1];
            southestFacetPoints[1] = supportVariable;
        }

        if(southestFacetPoints[2].x() < southestFacetPoints[3].x()){
            Point supportVariable = southestFacetPoints[2];
            southestFacetPoints[2] = southestFacetPoints[3];
            southestFacetPoints[3] = supportVariable;
        }


//        if(southestFacetPoints[2].y() == southestFacetPoints[3].y())
//        {
//            Point supportVariable = southestFacetPoints[2];
//            southestFacetPoints[2] = southestFacetPoints[3];
//            southestFacetPoints[3] = supportVariable;
//        }
    }
    else{
        std::cerr<<"Error: 4 points not passed, it is not possible make sort!"<<std::endl;
    }
}

//template<typename Point, typename Point, typename Point, typename Point>
void Point_sorter::sort_northest_points_facet(std::vector<Point> &points, std::vector<Point> &northestFacetPoints) {
    std::sort(points.begin(), points.end(), [](Point a, Point b) {return a.z() > b.z(); }); //sort by decreasing z coordinate
    if(points.size() >= 4){
        for(int i = 0; i < 4; i++)
        {
            northestFacetPoints.emplace_back(points[i]);
        }
        std::sort(northestFacetPoints.begin(), northestFacetPoints.end(), zComparator);

        // sort by Y
        iterator vector_it = northestFacetPoints.begin(),vector_end_it = northestFacetPoints.end();
        std::sort(vector_it, vector_end_it, yComparator);

        // group by Y
        std::vector<iterator> yGroups_it;
        groupByY(northestFacetPoints, yGroups_it, vector_it, vector_end_it);

        // sort the x coordinates
        for(iterator2 y_it = yGroups_it.begin(),y_it2 = ++yGroups_it.begin(), y_it_end = yGroups_it.end(); y_it!= y_it_end; ++y_it, ++y_it2){
            if(y_it2 != y_it_end) {
                std::sort(*y_it, *y_it2, xComparator);
            }
            else{
                std::sort(*y_it, northestFacetPoints.end(), xComparator);
            }
        }

        // sort to obtain the northest points facet order
        if(northestFacetPoints[0].x() > northestFacetPoints[1].x()){
            Point supportVariable = northestFacetPoints[0];
            northestFacetPoints[0] = northestFacetPoints[1];
            northestFacetPoints[1] = supportVariable;
        }

        if(northestFacetPoints[2].x() < northestFacetPoints[3].x()){
            Point supportVariable = northestFacetPoints[2];
            northestFacetPoints[2] = northestFacetPoints[3];
            northestFacetPoints[3] = supportVariable;
        }

        std::rotate(northestFacetPoints.begin(),
                        northestFacetPoints.end()-1, // this will be the new first element
                        northestFacetPoints.end());
    }
    else{
        std::cerr<<"Error: 4 points not passed, it is not possible make sort!"<<std::endl;
    }
}
