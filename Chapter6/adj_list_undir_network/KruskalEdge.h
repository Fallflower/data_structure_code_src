/*
 * @Author: Metaphor
 */
/*
 * @Author: Metaphor
 */
/*
 * @Author: Metaphor
 */
template<class ElemType,class WeightType>
class KruskalEdge
{
public:
    ElemType vertex1, vertex2;
    WeightType weight;
    KruskalEdge(ElemType v1, ElemType v2, WeightType w);
    KruskalEdge(){};
    KruskalEdge<ElemType, WeightType> &operator=(const KruskalEdge<ElemType, WeightType> &Ed);
    bool operator<=(const KruskalEdge<ElemType, WeightType> &Ed);
    bool operator>=(const KruskalEdge<ElemType, WeightType> &Ed);
    bool operator<(const KruskalEdge<ElemType, WeightType> &Ed);
    bool operator>(const KruskalEdge<ElemType, WeightType> &Ed);
};

template <class ElemType, class WeightType>
KruskalEdge<ElemType, WeightType>::KruskalEdge(ElemType v1, ElemType v2, WeightType w)
{
    vertex1 = v1;
    vertex2 = v2;
    weight = w;
}

template <class ElemType, class WeightType>
bool KruskalEdge<ElemType, WeightType>::operator<=(const KruskalEdge<ElemType,WeightType>& Ed)
{
    return (weight <= Ed.weight);
}

template <class ElemType, class WeightType>
bool KruskalEdge<ElemType, WeightType>::operator>=(const KruskalEdge<ElemType,WeightType>& Ed)
{
    return (weight >= Ed.weight);
}

template <class ElemType, class WeightType>
bool KruskalEdge<ElemType, WeightType>::operator<(const KruskalEdge<ElemType,WeightType>& Ed)
{
    return (weight < Ed.weight);
}

template <class ElemType, class WeightType>
bool KruskalEdge<ElemType, WeightType>::operator>(const KruskalEdge<ElemType,WeightType>& Ed)
{
    return (weight > Ed.weight);
}

template <class ElemType, class WeightType>
KruskalEdge<ElemType,WeightType>& KruskalEdge<ElemType, WeightType>::operator=(const KruskalEdge<ElemType,WeightType>& Ed)
{
    if (&Ed != this)
    {
        vertex1 = Ed.vertex1;
        vertex2 = Ed.vertex2;
        weight = Ed.weight;
    }
    return (*this);
}


template<class ElemType,class WeightType>
struct CloseArcType
{
	WeightType lowweight;
	int nearvertex;
};