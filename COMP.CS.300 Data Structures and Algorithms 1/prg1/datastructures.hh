// Datastructures.hh
//
// Student name: Jani Koistinen
// Student email: jani.koistinen@tuni.fi
// Student number: H268666

#ifndef DATASTRUCTURES_HH
#define DATASTRUCTURES_HH

#include <string>
#include <vector>
#include <tuple>
#include <utility>
#include <limits>
#include <functional>
#include <exception>
#include <iostream>
#include <QDebug>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <cmath>

// Types for IDs
using AffiliationID = std::string;
using PublicationID = unsigned long long int;
using Name = std::string;
using Year = unsigned short int;
using Weight = int;
using Distance = int;

// Return values for cases where required thing was not found
AffiliationID const NO_AFFILIATION = "---";
PublicationID const NO_PUBLICATION = -1;
Name const NO_NAME = "!NO_NAME!";
Year const NO_YEAR = -1;
Weight const NO_WEIGHT = -1;

// Return value for cases where integer values were not found
int const NO_VALUE = std::numeric_limits<int>::min();

// Type for a coordinate (x, y)
struct Coord
{
    int x = NO_VALUE;
    int y = NO_VALUE;
};

// struct for publications
struct Publication {
    PublicationID pub_id;
    Name pub_name;
    Year pub_year;
    std::vector<AffiliationID> pub_affiliations;
    PublicationID referenced_by;
    std::vector<PublicationID> referencing;
};

// struct for affiliations
struct Affiliation {
    AffiliationID id;
    Coord coords;
    Name name;
    std::vector<Publication> aff_publications;
    std::vector<PublicationID> aff_publication_ids;
};

using AffiliationIT = std::unordered_map<AffiliationID, Affiliation>::iterator;
using PublicationIT = std::unordered_map<PublicationID, Publication>::iterator;

// Example: Defining == and hash function for Coord so that it can be used
// as key for std::unordered_map/set, if needed
inline bool operator==(Coord c1, Coord c2) { return c1.x == c2.x && c1.y == c2.y; }
inline bool operator!=(Coord c1, Coord c2) { return !(c1==c2); } // Not strictly necessary

struct CoordHash
{
    std::size_t operator()(Coord xy) const
    {
        auto hasher = std::hash<int>();
        auto xhash = hasher(xy.x);
        auto yhash = hasher(xy.y);
        // Combine hash values (magic!)
        return xhash ^ (yhash + 0x9e3779b9 + (xhash << 6) + (xhash >> 2));
    }
};

// Example: Defining < for Coord so that it can be used
// as key for std::map/set
inline bool operator<(Coord c1, Coord c2)
{
    if (c1.y < c2.y) { return true; }
    else if (c2.y < c1.y) { return false; }
    else { return c1.x < c2.x; }
}

// Return value for cases where coordinates were not found
Coord const NO_COORD = {NO_VALUE, NO_VALUE};

// Return value for cases where Distance is unknown
Distance const NO_DISTANCE = NO_VALUE;

// This exception class is there just so that the user interface can notify
// about operations which are not (yet) implemented
class NotImplemented : public std::exception
{
public:
    NotImplemented() : msg_{} {}
    explicit NotImplemented(std::string const& msg) : msg_{msg + " not implemented"} {}

    virtual const char* what() const noexcept override
    {
        return msg_.c_str();
    }
private:
    std::string msg_;
};

// This is the class you are supposed to implement

class Datastructures
{
public:
    Datastructures();
    ~Datastructures();

    // Estimate of performance: O(1)
    // Short rationale for estimate: std::size is constant operation
    unsigned int get_affiliation_count();

    // Estimate of performance: O(n)
    // Short rationale for estimate: Destroys elements one by one
    void clear_all();

    // Estimate of performance: O(1)
    // Short rationale for estimate: returns a single already made vector
    std::vector<AffiliationID> get_all_affiliations();

    // Estimate of performance: O(1)
    // Short rationale for estimate: find from unordered map is constant on
    // average
    bool add_affiliation(AffiliationID id, Name const& name, Coord xy);

    // Estimate of performance: O(1)
    // Short rationale for estimate: find from unordered map is constant on
    // average
    Name get_affiliation_name(AffiliationID id);

    // Estimate of performance: O(1)
    // Short rationale for estimate: find from unordered map is constant on
    // average
    Coord get_affiliation_coord(AffiliationID id);


    // We recommend you implement the operations below only after implementing the ones above

    // Estimate of performance: O(n^2logn)
    // Short rationale for estimate: std::sort have effiency of nlogn and after
    // sort have to loop to build a returnable vector
    std::vector<AffiliationID> get_affiliations_alphabetically();

    // Estimate of performance: O(n^2logn)
    // Short rationale for estimate: std::sort have effiency of nlogn and after
    // sort have to loop to build a returnable vector
    std::vector<AffiliationID> get_affiliations_distance_increasing();

    // Estimate of performance: O(1)
    // Short rationale for estimate: find from unordered map is constant on
    // average
    AffiliationID find_affiliation_with_coord(Coord xy);

    // Estimate of performance: O(1)
    // Short rationale for estimate: find from unordered map is constant on
    // average
    bool change_affiliation_coord(AffiliationID id, Coord newcoord);


    // We recommend you implement the operations below only after implementing the ones above

    // Estimate of performance: O(1)
    // Short rationale for estimate: find from unordered map is constant on
    // average
    bool add_publication(PublicationID id, Name const& name, Year year, const std::vector<AffiliationID> /*& affiliations*/);

    // Estimate of performance: O(1)
    // Short rationale for estimate: returns a single already made vector
    std::vector<PublicationID> all_publications();

    // Estimate of performance: O(1)
    // Short rationale for estimate: find from unordered map is constant on
    // average
    Name get_publication_name(PublicationID id);

    // Estimate of performance: O(1)
    // Short rationale for estimate: find from unordered map is constant on
    // average
    Year get_publication_year(PublicationID id);

    // Estimate of performance: O(1)
    // Short rationale for estimate: find from unordered map is constant on
    // average
    std::vector<AffiliationID> get_affiliations(PublicationID id);

    // Estimate of performance: O(1)
    // Short rationale for estimate: find from unordered map is constant on
    // average
    bool add_reference(PublicationID id, PublicationID parentid);

    // Estimate of performance: O(1)
    // Short rationale for estimate: find from unordered map is constant on
    // average
    std::vector<PublicationID> get_direct_references(PublicationID id);

    // Estimate of performance: O(1)
    // Short rationale for estimate: find from unordered map is constant on
    // average
    bool add_affiliation_to_publication(AffiliationID affiliationid, PublicationID publicationid);

    // Estimate of performance: O(1)
    // Short rationale for estimate: find from unordered map is constant on
    // average
    std::vector<PublicationID> get_publications(AffiliationID id);

    // Estimate of performance: O(1)
    // Short rationale for estimate: find from unordered map is constant on
    // average
    PublicationID get_parent(PublicationID id);

    // Estimate of performance: O(n)
    // Short rationale for estimate: find from unordered map is constant on
    // average, so performance depends on the number of publications stored
    // under affiliation
    std::vector<std::pair<Year, PublicationID>> get_publications_after(AffiliationID affiliationid, Year year);

    // Estimate of performance: O(n)
    // Short rationale for estimate:find from unordered map is constant on
    // average and recursively loops through parentid after parentid until
    // NO_PUBLICATION
    std::vector<PublicationID> get_referenced_by_chain(PublicationID id);


    // Non-compulsory operations

    // Estimate of performance: O(n)
    // Short rationale for estimate: is dependant on size of vector containing
    // references
    std::vector<PublicationID> get_all_references(PublicationID id);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<AffiliationID> get_affiliations_closest_to(Coord xy);

    // Estimate of performance:
    // Short rationale for estimate:
    bool remove_affiliation(AffiliationID id);

    // Estimate of performance:
    // Short rationale for estimate:
    PublicationID get_closest_common_parent(PublicationID id1, PublicationID id2);

    // Estimate of performance:
    // Short rationale for estimate:
    bool remove_publication(PublicationID publicationid);


private:

    std::unordered_map<AffiliationID, Affiliation> affiliations;
    std::unordered_map<Coord, Affiliation, CoordHash> hash_aff;
    std::vector<Affiliation*> affiliations_vector;
    std::vector<AffiliationID> affiliation_ids;

    std::unordered_map<PublicationID, Publication> publications;
    std::vector<Publication*> publications_vector;
    std::vector<PublicationID> publication_ids;

    Affiliation empty_aff;
    Publication empty_pub;

    std::vector<PublicationID> create_empty_pub();
    std::vector<AffiliationID> create_empty_aff();
    Affiliation get_affiliation(AffiliationID id);
    std::vector<PublicationID> create_chain(PublicationID id, std::vector<PublicationID> temp);
    std::vector<PublicationID> create_all_references(Publication pub, std::vector<PublicationID> temp);

};

#endif // DATASTRUCTURES_HH
