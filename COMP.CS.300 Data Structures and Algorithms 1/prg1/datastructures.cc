// Datastructures.cc
//
// Student name: Jani Koistinen
// Student email: jani.koistinen@tuni.fi
// Student number: H268666

#include "datastructures.hh"

#include <random>

std::minstd_rand rand_engine; // Reasonably quick pseudo-random generator

template <typename Type>
Type random_in_range(Type start, Type end)
{
    auto range = end-start;
    ++range;

    auto num = std::uniform_int_distribution<unsigned long int>(0, range-1)(rand_engine);

    return static_cast<Type>(start+num);
}

// Modify the code below to implement the functionality of the class.
// Also remove comments from the parameter names when you implement
// an operation (Commenting out parameter name prevents compiler from
// warning about unused parameters on operations you haven't yet implemented.)

Datastructures::Datastructures()
{
    // Write any initialization you need here
    empty_aff.id = NO_AFFILIATION;
    empty_aff.coords = {NO_VALUE, NO_VALUE};
    empty_aff.name = NO_NAME;

    empty_pub.pub_id = NO_PUBLICATION;
}

Datastructures::~Datastructures()
{
    // Write any cleanup you need here
    affiliations.clear();
    hash_aff.clear();
    affiliations_vector.clear();
    affiliation_ids.clear();  

    publications.clear();
    publications_vector.clear();
    publication_ids.clear();
}

unsigned int Datastructures::get_affiliation_count()
{
    // Replace the line below with your implementation
    //throw NotImplemented("get_affiliation_count()");
    return affiliations.size();
}

void Datastructures::clear_all()
{
    // Replace the line below with your implementation
    //throw NotImplemented("clear_all()");
    affiliations.clear();
    hash_aff.clear();
    affiliations_vector.clear();
    affiliation_ids.clear();

    publications.clear();
    publications_vector.clear();
    publication_ids.clear();
}

std::vector<AffiliationID> Datastructures::get_all_affiliations()
{
    // Replace the line below with your implementation
    //throw NotImplemented("get_all_affiliations()");
    return affiliation_ids;
}

bool Datastructures::add_affiliation(AffiliationID new_id, const Name &new_name, Coord new_xy)
{
    // Replace the line below with your implementation
    //throw NotImplemented("add_affiliation()");
    Affiliation temp;
    AffiliationIT it_new = affiliations.find(new_id);
    if ( it_new != affiliations.end() ) {
        return false;
    }
    temp.id = new_id;
    temp.name = new_name;
    temp.coords = new_xy;
    affiliations.insert({new_id, temp});
    hash_aff.insert({new_xy, temp});
    AffiliationIT it = affiliations.find(new_id);
    if( it != affiliations.end() ) {
        affiliations_vector.push_back(&it->second);
        affiliation_ids.push_back(it->second.id);
    }
    return true;
}

Name Datastructures::get_affiliation_name(AffiliationID id)
{
    // Replace the line below with your implementation
    //throw NotImplemented("get_affiliation_name()");
    Affiliation temp = get_affiliation(id);
    if( temp.id == NO_AFFILIATION ) { return NO_NAME; }
    return temp.name;
}

Coord Datastructures::get_affiliation_coord(AffiliationID id)
{
    // Replace the line below with your implementation
    //throw NotImplemented("get_affiliation_coord()");
    Affiliation temp = get_affiliation(id);
    if( temp.id == NO_AFFILIATION ) { return {NO_VALUE, NO_VALUE}; }
    return temp.coords;
}

// We recommend you implement the operations below only after implementing the ones above

std::vector<AffiliationID> Datastructures::get_affiliations_alphabetically()
{
    // Replace the line below with your implementation
    //throw NotImplemented("get_affiliations_alphabetically()");
    std::vector<AffiliationID> temp;
    temp.reserve(affiliations.size());
    sort(affiliations_vector.begin(), affiliations_vector.end(), [](Affiliation* a, Affiliation* b) {
        return a->name < b->name;
    });
    std::vector<Affiliation*>::iterator it = affiliations_vector.begin();
    while( it != affiliations_vector.end() ) {
        temp.push_back((*it)->id);
        it++;
    }

    return temp;
}

std::vector<AffiliationID> Datastructures::get_affiliations_distance_increasing()
{
    // Replace the line below with your implementation
    //throw NotImplemented("get_affiliations_distance_increasing()");
    std::vector<AffiliationID> temp_ids;
    temp_ids.reserve(affiliations_vector.size());

    sort(affiliations_vector.begin(), affiliations_vector.end(), [](Affiliation* a, Affiliation* b) {
        double sqrt_a = sqrt(pow(a->coords.x, 2) + pow(a->coords.y, 2));
        double sqrt_b = sqrt(pow(b->coords.x, 2) + pow(b->coords.y, 2));
        if( sqrt_a == sqrt_b ) {
            return a->coords.y < b->coords.y;
        }
        return sqrt_a < sqrt_b;
    });
    std::vector<Affiliation*>::iterator it = affiliations_vector.begin();
    while( it != affiliations_vector.end() ) {
        temp_ids.push_back((*it)->id);
        it++;
    }
    return temp_ids;
}

AffiliationID Datastructures::find_affiliation_with_coord(Coord xy)
{
    // Replace the line below with your implementation
    //throw NotImplemented("find_affiliation_with_coord()");
    std::unordered_map<Coord, Affiliation, CoordHash>::iterator it = hash_aff.find(xy);
    if( it != hash_aff.end() ) {
        return it->second.id;
    }
    return NO_AFFILIATION;
}

bool Datastructures::change_affiliation_coord(AffiliationID id, Coord newcoord)
{
    // Replace the line below with your implementation
    //throw NotImplemented("change_affiliation_coord()");

    AffiliationIT it = affiliations.find(id);
    if( it != affiliations.end() ) {
        std::unordered_map<Coord, Affiliation, CoordHash>::iterator it_coord = hash_aff.find(it->second.coords);
        if( it_coord != hash_aff.end() ) {
            it->second.coords = newcoord;
            hash_aff.erase(it_coord);
            hash_aff.insert({newcoord, it->second});
            return true;
        }
    }
    return false;
}

bool Datastructures::add_publication(PublicationID id, const Name &name, Year year, const std::vector<AffiliationID> /*&affiliations*/)
{
    // Replace the line below with your implementation
    //throw NotImplemented("add_publication()");
    PublicationIT it_new = publications.find(id);
    if( it_new != publications.end()  ) {
        return false;
    }
    Publication temp;
    temp.pub_id = id;
    temp.pub_name = name;
    temp.pub_year = year;
    temp.referenced_by = NO_PUBLICATION;
    publications.insert({id, temp});
    PublicationIT it = publications.find(id);
    if( it != publications.end()  ) {
        publications_vector.push_back(&it->second);
        publication_ids.push_back(it->second.pub_id);
    }
    return true;
}

std::vector<PublicationID> Datastructures::all_publications()
{
    // Replace the line below with your implementation
    //throw NotImplemented("all_publications()");
    return publication_ids;
}

Name Datastructures::get_publication_name(PublicationID id)
{
    // Replace the line below with your implementation
    //throw NotImplemented("get_publication_name()");
    PublicationIT it = publications.find(id);
    if( it != publications.end() ) {
        return it->second.pub_name;
    }
    return NO_NAME;
}

Year Datastructures::get_publication_year(PublicationID id)
{
    // Replace the line below with your implementation
    //throw NotImplemented("get_publication_year()");
    PublicationIT it = publications.find(id);
    if( it != publications.end() ) {
        return it->second.pub_year;
    }
    return NO_YEAR;
}

std::vector<AffiliationID> Datastructures::get_affiliations(PublicationID id)
{
    // Replace the line below with your implementation
    //throw NotImplemented("get_affiliations()");
    PublicationIT it = publications.find(id);
    if( it != publications.end() ) {
        if ( it->second.pub_affiliations.empty() ) {
            std::vector<AffiliationID> empty;
            return empty;
        } else {
                return it->second.pub_affiliations;
        }
    }
    std::vector<AffiliationID> empty;
    return empty;
}

bool Datastructures::add_reference(PublicationID id, PublicationID parentid)
{
    // Replace the line below with your implementation
    //throw NotImplemented("add_reference()");
    PublicationIT it_parent = publications.find(parentid);
    if( it_parent != publications.end() ) {
        PublicationIT it_id = publications.find(id);
        if( it_id != publications.end() ) {
                it_parent->second.referencing.push_back(id);
                it_id->second.referenced_by = parentid;
                return true;
        }
    }
    return false;
}

std::vector<PublicationID> Datastructures::get_direct_references(PublicationID id)
{
    // Replace the line below with your implementation
    //throw NotImplemented("get_direct_references()");
    PublicationIT it = publications.find(id);
    if( it != publications.end() ) {
        return it->second.referencing;
    }
    return create_empty_pub();
}

bool Datastructures::add_affiliation_to_publication(AffiliationID affiliationid, PublicationID publicationid)
{
    // Replace the line below with your implementation
    //throw NotImplemented("add_affiliation_to_publication()");
    AffiliationIT it_aff = affiliations.find(affiliationid);
    if( it_aff != affiliations.end() ) {
        PublicationIT it_pub = publications.find(publicationid);
        if( it_pub != publications.end() ) {
            it_aff->second.aff_publications.push_back(it_pub->second);
            it_aff->second.aff_publication_ids.push_back(publicationid);
            it_pub->second.pub_affiliations.push_back(affiliationid);
            return true;
        }
    }
    return false;
}

std::vector<PublicationID> Datastructures::get_publications(AffiliationID id)
{
    // Replace the line below with your implementation
    //throw NotImplemented("get_publications()");
    AffiliationIT it = affiliations.find(id);
    if( it != affiliations.end() and not it->second.aff_publication_ids.empty() ) {
        return it->second.aff_publication_ids;
    }
    std::vector<PublicationID> empty;
    return empty;
}

PublicationID Datastructures::get_parent(PublicationID id)
{
    // Replace the line below with your implementation
    //throw NotImplemented("get_parent()");
    PublicationIT it = publications.find(id);
    if( it != publications.end() ) {
        return it->second.referenced_by;
    }
    return NO_PUBLICATION;
}

std::vector<std::pair<Year, PublicationID> > Datastructures::get_publications_after(AffiliationID affiliationid, Year year)
{
    // Replace the line below with your implementation
    //throw NotImplemented("get_publications_after()");
    std::vector<std::pair<Year, PublicationID>> temp;
    AffiliationIT it = affiliations.find(affiliationid);
    if( it != affiliations.end() ) {
        std::vector<Publication>::iterator it_pub = it->second.aff_publications.begin();
        while( it_pub != it->second.aff_publications.end() ) {
            if( it_pub->pub_year >= year ) {
                temp.push_back({it_pub->pub_year, it_pub->pub_id});
            }
            it_pub++;
        }
        return temp;
    }
    temp.push_back({NO_YEAR, NO_PUBLICATION});
    return temp;
}

std::vector<PublicationID> Datastructures::get_referenced_by_chain(PublicationID id)
{
    // Replace the line below with your implementation
    //throw NotImplemented("get_referenced_by_chain()");
    std::vector<PublicationID> temp;
    PublicationIT it = publications.find(id);
    if( it != publications.end() ) {
        return create_chain(it->second.pub_id, temp);
    }
    temp.push_back(NO_PUBLICATION);
    return temp;
}

// voluntary functions

std::vector<PublicationID> Datastructures::get_all_references(PublicationID id)
{
    // Replace the line below with your implementation
    //throw NotImplemented("get_all_references()");
    std::vector<PublicationID> temp;
    PublicationIT it = publications.find(id);
    if( it != publications.end() ) {
        return create_all_references(it->second, temp);
    }
    temp.push_back(NO_PUBLICATION);
    return temp;
}

std::vector<AffiliationID> Datastructures::get_affiliations_closest_to(Coord /*xy*/)
{
    // Replace the line below with your implementation
    throw NotImplemented("get_affiliations_closest_to()");
}

bool Datastructures::remove_affiliation(AffiliationID /*id*/)
{
    // Replace the line below with your implementation
    throw NotImplemented("remove_affiliation()");
}

PublicationID Datastructures::get_closest_common_parent(PublicationID /*id1*/, PublicationID /*id2*/)
{
    // Replace the line below with your implementation
    throw NotImplemented("get_closest_common_parent()");
}

bool Datastructures::remove_publication(PublicationID /*publicationid*/)
{
    // Replace the line below with your implementation
    throw NotImplemented("remove_publication()");
}

// own added private functions

std::vector<PublicationID> Datastructures::create_empty_pub()
{
    std::vector<PublicationID> temp;
    temp.push_back(NO_PUBLICATION);
    return temp;
}

std::vector<AffiliationID> Datastructures::create_empty_aff()
{
    std::vector<AffiliationID> temp;
    temp.push_back(NO_AFFILIATION);
    return temp;
}

Affiliation Datastructures::get_affiliation(AffiliationID id)
{
    AffiliationIT it = affiliations.find(id);
    if( it != affiliations.end() ) {
        return it->second;
    }
    return empty_aff;
}

std::vector<PublicationID> Datastructures::create_chain(PublicationID id, std::vector<PublicationID> temp)
{
    PublicationID parentid = get_parent(id);
    if( parentid == NO_PUBLICATION) {
        return temp;
    } else {
        temp.push_back(parentid);
        return create_chain(parentid, temp);
    }
}

std::vector<PublicationID> Datastructures::create_all_references(Publication pub, std::vector<PublicationID> temp)
{
    if( pub.referencing.empty() ) {
        return temp;
    }
    std::vector<PublicationID>::iterator it = pub.referencing.begin();
    while( it != pub.referencing.end() ) {
        temp.insert(temp.end(), pub.referencing.begin(), pub.referencing.end() );
        PublicationIT iter = publications.find(*it);
        if( iter != publications.end() ) {
            return create_all_references(iter->second, temp);
        }
        it++;
    }
    return temp;
}





