#ifndef __H_TEMPLATED_MAP_VECTOR__
#define __H_TEMPLATED_MAP_VECTOR__

#include <string>
#include <map>
#include <vector>
#include <assert.h>

#include "CheckedDelete.h"

namespace mBase {
    template<class T>
    class TemplatedMapVector
    {
    public:
        class MapResourceValue
        {
        public:
            T *m_Value;
            size_t m_Id;
            MapResourceValue(){ assert(!"Method must not be called"); }
            MapResourceValue(T *aValue, size_t aId) : m_Value(aValue), m_Id(aId){}
        };

        typedef std::vector<T *> TVectorResources;
        typedef std::map<std::string, MapResourceValue> TMapResources;

    public:
        TemplatedMapVector(){}
        virtual ~TemplatedMapVector()
        {
            Destroy();
        }

        size_t GetCount()
        {
            return m_ResourcesVector.size();
        }

        bool Exist(const std::string &aName)
        {
            return m_ResourcesMap.find(aName) != m_ResourcesMap.end();
        }

        void Remove(const std::string &aName)
        {
            MapResourceValue l_ResourceValue = m_ResourcesMap[aName];
            size_t index = l_ResourceValue.m_Id;
            CheckedDelete(m_ResourcesVector[index]);
            CheckedDelete(m_ResourcesMap[aName]);
            m_ResourcesMap.erase(aName);
            m_ResourcesVector.erase(m_ResourcesVector.begin() + index);
            for (auto lItb = m_ResourcesMap.begin(); lItb != m_ResourcesMap.end(); ++lItb)
            {
                if (lItb->second->m_Id > index)
                {
                    lItb->second->m_Id--;
                }
            }
        }

        virtual T * operator[](size_t aId)
        {
            return m_ResourcesVector[aId];
        }

        virtual T * operator()(const std::string &aName)
        {
            auto lItfind = m_ResourcesMap.find(aName);
            return (lItfind != m_ResourcesMap.end()) ? lItfind->second.m_Value : nullptr;
        }

        virtual bool Add(const std::string &aName, T *Resource)
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
            for (int i = 0; i < m_ResourcesVector.size(); ++i)
            {
                CheckedDelete(m_ResourcesVector[i]);
            }
            Clear();
        }

    protected:
        TVectorResources m_ResourcesVector;
        TMapResources	 m_ResourcesMap;
    };
}

#endif // __H_TEMPLATED_MAP_VECTOR__