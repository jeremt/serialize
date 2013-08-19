
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
 * @param f The field to serialize.
 * @param b Serialize method do not exists.
 */
template<typename FieldType, typename StreamType>
auto _serialize(StreamType &os, FieldType const &f, false_t b)
    -> decltype(f, void()) {
  static_cast<void>(b);
  os.basicSerialize(f);
}

/**
 * Call serialization from .serialize() method.
 * @param os The stream serializer class.
 * @param f The field to serialize.
 * @param b Serialize method exists.
 */ 
template<typename FieldType, typename StreamType>
auto _serialize(StreamType &os, FieldType const &f, true_t b)
    -> decltype(f.serialize(os), void()) {
  static_cast<void>(b);
  std::cout << "serialize from method" << std::endl;
  f.serialize(os);
}

/**
 * Call basic types deserialization.
 * @param is The stream deserializer class.
 * @param f The field to deserialize.
 * @param b Deserialize method do not exists.
 */
template<typename FieldType, typename StreamType>
auto _deserialize(StreamType &is, FieldType &f, false_t b)
    -> decltype(f, void()) {
  static_cast<void>(b);
  is.basicDeserialize(f);
}

/**
 * Call deserialization from .deserialize() method.
 * @param is The stream deserializer class.
 * @param f The field to deserialize.
 * @param b Deserialize method exists.
 */ 
template<typename FieldType, typename StreamType>
auto _deserialize(StreamType &is, FieldType &f, true_t b)
    -> decltype(f.deserialize(is), void()) {
  static_cast<void>(b);
  f.deserialize(is);
}

} // !detail::

#endif // !SERIALIZE_DETAILS_INL_