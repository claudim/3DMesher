#include "External_facet_finder.h"

//template<typename allocator, typename Linear_cell_complex_traits, typename allocator, typename Linear_cell_complex_traits, typename allocator, typename Linear_cell_complex_traits, typename allocator, typename Linear_cell_complex_traits>
std::vector<Dart_const_handle> External_facet_finder::find(const LCC_3 & lcc){
    std::vector<Dart_const_handle> externalFacets = std::vector<Dart_const_handle>();
    if(!lcc.is_empty())
    {
        for(LCC_3::One_dart_per_cell_const_range<2,3>::const_iterator cell_facet_iterator = lcc.one_dart_per_cell<2,3>().begin(),
                    cell_facet_end_iterator = lcc.one_dart_per_cell<2, 3>().end();
            cell_facet_iterator != cell_facet_end_iterator; ++cell_facet_iterator){
            Dart_const_handle near_cell_facet_dart_handle = lcc.beta(cell_facet_iterator, 3);
            if (is_near_cell_facet_null(lcc, near_cell_facet_dart_handle))
            {
                externalFacets.push_back(cell_facet_iterator);
            }
        }
    }
    return externalFacets;
}

std::vector<Dart_handle> External_facet_finder::findFacets(LCC_3 & lcc){
    std::vector<Dart_handle> externalFacets;
    if(!lcc.is_empty())
    {
        for(LCC_3::One_dart_per_cell_range<2,3>::iterator cell_facet_iterator = lcc.one_dart_per_cell<2,3>().begin(),
                    cell_facet_end_iterator = lcc.one_dart_per_cell<2, 3>().end();
            cell_facet_iterator != cell_facet_end_iterator; ++cell_facet_iterator){
            Dart_const_handle near_cell_facet_dart_handle = lcc.beta(cell_facet_iterator, 3);
            if (is_near_cell_facet_null(lcc, near_cell_facet_dart_handle))
            {
                externalFacets.push_back(cell_facet_iterator);
            }
        }
    }
    return externalFacets;
}

bool External_facet_finder::is_near_cell_facet_null(const LCC_3 &lcc,
                                                    const Dart_const_handle &near_cell_facet_dart_handle) const {
    return near_cell_facet_dart_handle == lcc.null_dart_handle;
}

bool External_facet_finder::is_near_cell_facet_null(const LCC_3 &lcc,
                                                    const Dart_handle &near_cell_facet_dart_handle) const {
    return near_cell_facet_dart_handle == lcc.null_dart_handle;
}

/**
 * Find the external facet of a block if there are.
 *
 * @param lcc Set of blocks who the block belongs.
 * @param block Block whose it wants find the external facets.
 * @return The external facets or a vector with zero size.
 */
std::vector<Dart_handle> External_facet_finder::find(LCC_3 & lcc, Dart_handle block){
    std::vector<Dart_handle> externalFacets;
    if(!lcc.is_empty())
    {
        for(LCC_3::One_dart_per_incident_cell_range<2,3,3>::iterator cell_facet_iterator = lcc.one_dart_per_incident_cell<2,3,3>(block).begin(),
                    cell_facet_end_iterator = lcc.one_dart_per_incident_cell<2,3,3>(block).end();
            cell_facet_iterator != cell_facet_end_iterator; ++cell_facet_iterator){
            Dart_const_handle near_cell_facet_dart_handle = lcc.beta(cell_facet_iterator, 3);
            if (is_near_cell_facet_null(lcc, near_cell_facet_dart_handle))
            {
                externalFacets.push_back(cell_facet_iterator);
            }
        }
    }
    return externalFacets;
}


