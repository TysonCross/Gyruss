//
// Created by chris on 2017/09/10.
//

#ifndef PROJECT_RESOURCEMAPPER_H
#define PROJECT_RESOURCEMAPPER_H

#include <string>
#include <vector>
#include <map>

using resourceMap = std::map<std::string, std::vector<std::string> >;
//template<class Type>
//    using resourceMap = std::map<std::string, std::vector<Type>>;

class ResourceMapper
{
public:
    ResourceMapper();
    const resourceMap getResourceMap() const;
    const std::vector<std::string> getResourceValues(std::string) const;
    const std::string getResource(std::string) const;

private:
    resourceMap _resourceMap;
};

#endif //PROJECT_RESOURCEMAPPER_H