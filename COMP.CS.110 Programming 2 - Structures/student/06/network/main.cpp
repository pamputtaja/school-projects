#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

const std::string HELP_TEXT = "S = store id1 i2\nP = print id\n"
                              "C = count id\nD = depth id\n";


std::vector<std::string> split(const std::string& s,
                               const char delimiter,
                               bool ignore_empty = false)
{
    std::vector<std::string> result;
    std::string tmp = s;

    while(tmp.find(delimiter) != std::string::npos)
    {
        std::string new_part = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter) + 1, tmp.size());
        if(not (ignore_empty and new_part.empty()))
        {
            result.push_back(new_part);
        }
    }
    if(not (ignore_empty and tmp.empty()))
    {
        result.push_back(tmp);
    }
    return result;
}

void store(std::string key, std::string value,
           std::map< std::string, std::vector< std::string > > &persons )
{
    if(persons.find(key) == persons.end()) {
        persons.insert({key, {}});
    }
    persons.at(key).push_back(value);
}

void print(std::map< std::string, std::vector< std::string > > const &persons,
           std::string id, std::string ident = "")
{
    if(persons.find(id) == persons.end() || persons.at(id).empty()) {
        std::cout << ident << id << std::endl;
    } else {
        std::cout << ident << id << std::endl;
        std::vector<std::string>::const_iterator iter = persons.at(id).begin();
        for(; iter != persons.at(id).end(); iter++) {
            print(persons, *iter, ident + "..");
        }

    }
}

int count (std::map< std::string, std::vector< std::string > > const &persons,
           std::string id)
{
    if(persons.find(id) == persons.end() || persons.at(id).empty()) {
        return 0;
    } else {
        std::vector<std::string>::const_iterator iter = persons.at(id).begin();
        int size = persons.at(id).size();
        for(; iter != persons.at(id).end(); iter++) {
            size += count(persons, *iter);
        }
        return size;
    }
}

int depth(std::map< std::string, std::vector< std::string > > const &persons,
          std::string key)
{
    int max_depth = 0;
    if(persons.find(key) != persons.end()) {
        for(std::string id : persons.at(key)) {
            if(depth(persons, id) > max_depth) {
                max_depth = depth(persons, id);
            }
        }
    }
    return max_depth + 1;
}

int main()
{
    // TODO: Implement the datastructure here
    std::map< std::string, std::vector< std::string > > persons;

    while(true)
    {
        std::string line;
        std::cout << "> ";
        getline(std::cin, line);
        std::vector<std::string> parts = split(line, ' ', true);

        // Allowing empty inputs
        if(parts.size() == 0)
        {
            continue;
        }

        std::string command = parts.at(0);

        if(command == "S" or command == "s")
        {
            if(parts.size() != 3)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id1 = parts.at(1);
            std::string id2 = parts.at(2);

            // TODO: Implement the command here!
            store(id1, id2, persons);

        }
        else if(command == "P" or command == "p")
        {
            if(parts.size() != 2)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            // TODO: Implement the command here!
            print(persons, id);

        }
        else if(command == "C" or command == "c")
        {
            if(parts.size() != 2)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            // TODO: Implement the command here!
            std::cout << count(persons, id) << std::endl;

        }
        else if(command == "D" or command == "d")
        {
            if(parts.size() != 2)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            // TODO: Implement the command here!
            std::cout << depth(persons, id) << std::endl;

        }
        else if(command == "Q" or command == "q")
        {
           return EXIT_SUCCESS;
        }
        else
        {
            std::cout << "Erroneous command!" << std::endl << HELP_TEXT;
        }
    }
}
