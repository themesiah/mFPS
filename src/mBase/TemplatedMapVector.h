#ifndef __H_TEMPLATED_MAP_VECTOR__
#define __H_TEMPLATED_MAP_VECTOR__

#include <string>
#include <map>
#include <vector>
#include <assert.h>
#include <memory>

#include "CheckedDelete.h"

namespace mBase
{
    template <class T>
    class TemplatedMapVector
    {
    public:
        class MapResourceValue
        {
        public:
            std::shared_ptr<T> m_Value;
            size_t m_Id;
            MapResourceValue() { assert(!"Method must not be called"); }
            MapResourceValue(std::shared_ptr<T> aValue, size_t aId) : m_Value(aValue), m_Id(aId) {}
        };

        typedef std::vector<std::shared_ptr<T>> TVectorResources;
        typedef std::map<std::string, MapResourceValue> TMapResources;

    public:
        TemplatedMapVector() {}
        virtual ~TemplatedMapVector()
        {
            Destroy();
        }

        size_t GetCount() const
        {
            return m_ResourcesVector.size();
        }

        bool Exist(const std::string &aName) const
        {
            return m_ResourcesMap.find(aName) != m_ResourcesMap.end();
        }

        virtual void Remove(const std::string &aName)
        {
            MapResourceValue l_ResourceValue = m_ResourcesMap[aName];
            size_t index = l_ResourceValue.m_Id;
            // CheckedDelete(m_ResourcesVector[index]);
            // CheckedDelete(m_ResourcesMap[aName]);
            m_ResourcesMap.erase(aName);
            m_ResourcesVector.erase(m_ResourcesVector.begin() + index);
            for (auto lItb = m_ResourcesMap.begin(); lItb != m_ResourcesMap.end(); ++lItb)
            {
                // if (lItb->second->m_Id > index)
                //{
                //     lItb->second->m_Id--;
                // }
            }
        }

        virtual std::shared_ptr<T> operator[](size_t aId) const
        {
            return m_ResourcesVector[aId];
        }

        virtual std::shared_ptr<T> operator()(const std::string &aName) const
        {
            auto lItfind = m_ResourcesMap.find(aName);
            return (lItfind != m_ResourcesMap.end()) ? lItfind->second.m_Value : nullptr;
        }

        virtual bool Add(const std::string &aName, std::shared_ptr<T> Resource)
        {
            bool lOk = false;
            if (m_ResourcesMap.find(aName) == m_ResourcesMap.end())
            {
                m_ResourcesMap.insert(std::pair<std::string, MapResourceValue>(aName, MapResourceValue(Resource, m_ResourcesVector.size())));
                m_ResourcesVector.push_back(Resource);
                lOk = true;
            }
            return lOk;
        }

        virtual void Clear()
        {
            m_ResourcesMap.clear();
            m_ResourcesVector.clear();
        }

        virtual void Destroy()
        {
            Clear();
        }

    protected:
        TVectorResources m_ResourcesVector;
        TMapResources m_ResourcesMap;
    };
}

#endif // __H_TEMPLATED_MAP_VECTOR__