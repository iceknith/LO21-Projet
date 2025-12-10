#ifndef LO21_PROJET_SERIALIZABLE_HPP
#define LO21_PROJET_SERIALIZABLE_HPP

#include <QVariantMap>

class SerializationContext;

class Serializable {
public:
    virtual void serialize( QVariantMap& data, SerializationContext* context ) const = 0;
    virtual void deserialize( const QVariantMap& data, SerializationContext* context ) = 0;
    virtual string className()=0;
};


#endif //LO21_PROJET_SERIALIZABLE_HPP
