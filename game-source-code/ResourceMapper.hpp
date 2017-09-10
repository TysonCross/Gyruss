//
// Created by chris on 2017/09/10.
//

#ifndef PROJECT_RESOURCEMAPPER_H
#define PROJECT_RESOURCEMAPPER_H



#include <string>
#include <vector>
#include <map>


class ResourceMapper
{
public:
    ResourceMapper();
    const std::map<std::string, std::vector<std::string>> getResourceMap() const;
    const std::string getResource(std::string) const;

private:
    std::map<std::string, std::vector<std::string>> _resourceMap;
};

#endif //PROJECT_RESOURCEMAPPER_H