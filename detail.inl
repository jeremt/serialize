
#ifndef SERIALIZE_DETAILS_INL_
# define SERIALIZE_DETAILS_INL_

namespace detail {

/**
 * Some boolean typedef to call method by polymorphism.
 */
typedef int true_t;
typedef long false_t;

/**
 * Call basic types serialization.
 * @param os The stream serializer class.
 * @param obj The object to serialize.
 * @param false_t Serialize method do not exists.
 */
template<typename ObjType, typename StreamType>
auto _serialize(StreamType &os, ObjType const &obj, false_t)
    -> decltype(obj, void()) {
  os.basicSerialize(obj);
}

/**
 * Call serialization from .serialize() method.
 * @param os The stream serializer class.
 * @param obj The object to serialize.
 * @param true_t Serialize method exists.
 */ 
template<typename ObjType, typename StreamType>
auto _serialize(StreamType& os, ObjType const& obj, true_t)
    -> decltype(obj.serialize(os), void()) {
  obj.serialize(os);
}

}

#endif // !SERIALIZE_DETAILS_INL_