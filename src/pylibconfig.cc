#include <boost/python.hpp>
#include <libconfig.h++>
#include <string>

using namespace boost::python;
using namespace libconfig;

class pyConfig
{
public:
    pyConfig ()
    {
        config = new Config ();
    }

    ~pyConfig ()
    {
        delete config;
    }

    void read ( FILE * stream )
    {   config->read ( stream );    }

    void write ( FILE * stream )
    {   config->write ( stream );   }

    void readFile ( const char * filename )
    {   config->readFile ( filename ); }

    void writeFile ( const char * filename )
    {   config->writeFile ( filename );    }

    bool getAutoConvert ()
    {   return config->getAutoConvert (); }

    void setAutoConvert ( bool flag )
    {   config->setAutoConvert ( flag );  }

    bool exists ( const char * path )
    {   return config->exists ( path ); }

    tuple value ( const char * path )
    {   
        std::string v_string;
        if ( config->lookupValue ( path, v_string ) )
            return make_tuple ( v_string.c_str(), true );

        unsigned int v_uint;
        if ( config->lookupValue ( path, v_uint ) )
            return make_tuple ( v_uint, true );

        int v_int;
        if ( config->lookupValue ( path, v_int ) )
            return make_tuple ( v_int, true );

        bool v_bool;
        if ( config->lookupValue ( path, v_bool ) )
            return make_tuple ( v_bool, true );

        unsigned long long v_ulonglong;
        if ( config->lookupValue ( path, v_ulonglong ) )
            return make_tuple ( v_ulonglong, true );

        long long v_longlong;
        if ( config->lookupValue ( path, v_longlong ) )
            return make_tuple ( v_longlong, true );

        float v_float;
        if ( config->lookupValue ( path, v_float ) )
            return make_tuple ( v_float, true );

        double v_double;
        if ( config->lookupValue ( path, v_double ) )
            return make_tuple ( v_double, true );

        return make_tuple ( "", false );
    }

    list children_root ()
    {
        list result;
        int length = config->getRoot ().getLength ();
        for ( int index = 0; index < length; index++ )
        {
            result.append ( config->getRoot () [ index ].getPath ().c_str () );
        }
        return result;
    }

    list children ( const char * path )
    {
        list result;
        try {
            list result;
            int length = config->lookup ( path ).getLength ();
            for ( int index = 0; index < length; index++ )
            {
                result.append ( config->lookup ( path ) [ index ].getPath ().c_str () );
            }
            return result;
        }
        catch ( SettingNotFoundException & e )
        {
            return result;
        }
    }

    void remove ( const char * path, const char * name )
    {
        config->lookup ( path ).remove ( name );
    }

    void addBoolean ( const char * path, const char * name )
    {
        config->lookup ( path ).add ( name, libconfig::Setting::TypeBoolean );
    }

    void addBigInteger ( const char * path, const char * name )
    {
        config->lookup ( path ).add ( name, libconfig::Setting::TypeInt64 );
    }

    void addInteger ( const char * path, const char * name )
    {
        config->lookup ( path ).add ( name, libconfig::Setting::TypeInt );
    }

    void addFloat ( const char * path, const char * name )
    {
        config->lookup ( path ).add ( name, libconfig::Setting::TypeFloat );
    }

    void addString ( const char * path, const char * name )
    {
        config->lookup ( path ).add ( name, libconfig::Setting::TypeString );
    }

    void addGroup ( const char * path, const char * name )
    {
        config->lookup ( path ).add ( name, libconfig::Setting::TypeGroup );
    }

    void addList ( const char * path, const char * name )
    {
        config->lookup ( path ).add ( name, libconfig::Setting::TypeList );
    }

    void addArray_str ( const char * path, const char * name )
    {
        config->lookup ( path ).add ( name, libconfig::Setting::TypeArray );
    }
    void addArray ( const char * path )
    {
        config->lookup ( path ).add ( libconfig::Setting::TypeArray );
    }

    void appendToList_int ( const char * path, int value )
    {
        config->lookup ( path ).add ( libconfig::Setting::TypeInt ) = value;
    }

    void appendToList_bool ( const char * path, bool value)
    {
        config->lookup ( path ).add ( libconfig::Setting::TypeBoolean ) = value;
    }

    void appendToList_float ( const char * path, float value )
    {
        config->lookup ( path ).add ( libconfig::Setting::TypeFloat ) = value;
    }

    void appendToList_double ( const char * path, double value )
    {
        config->lookup ( path ).add ( libconfig::Setting::TypeFloat ) = value;
    }

    void appendToList_longlong ( const char * path, long long value )
    {
        config->lookup ( path ).add ( libconfig::Setting::TypeInt64 ) = value;
    }
    void appendToList_long( const char * path, long value )
    {
        config->lookup ( path ).add ( libconfig::Setting::TypeInt ) = value;
    }
    void appendToList_str ( const char * path, const char * value )
    {
        config->lookup ( path ).add ( libconfig::Setting::TypeString ) = value;
    }


    void appendToList_Group ( const char * path )
    {
        config->lookup ( path ).add ( libconfig::Setting::TypeGroup );
    }


    void setValue_bool ( const char * path, bool value )
    {
        config->lookup ( path ) = value;
    }

    void setValue_int ( const char * path, int value )
    {
        config->lookup ( path ) = value;
    }

    void setValue_long ( const char * path, long value )
    {
        config->lookup ( path ) = value;
    }

    void setValue_longlong ( const char * path, long long value )
    {
        config->lookup ( path ) = value;
    }

    void setValue_float ( const char * path, float value )
    {
        config->lookup ( path ) = value;
    }

    void setValue_double ( const char * path, double value )
    {
        config->lookup ( path ) = value;
    }

    void setValue_str ( const char * path, std::string value )
    {
        config->lookup ( path ) = value;
    }

private:
    Config * config;
};

BOOST_PYTHON_MODULE ( pylibconfig )
{
    class_<pyConfig>("Config")
        .def("read", &pyConfig::read )
        .def("write", &pyConfig::write )
        .def("readFile", &pyConfig::readFile )
        .def("writeFile", &pyConfig::writeFile )
        .def("getAutoConvert", &pyConfig::getAutoConvert )
        .def("setAutoConvert", &pyConfig::setAutoConvert )
        .def("exists", &pyConfig::exists )
        .def("children", &pyConfig::children )
        .def("children", &pyConfig::children_root )
        .def("value", &pyConfig::value )
        .def("remove", &pyConfig::remove )
        .def("addString", &pyConfig::addString )
        .def("addBoolean", &pyConfig::addBoolean )
        .def("addBigInteger", &pyConfig::addBigInteger )
        .def("addInteger", &pyConfig::addInteger )
        .def("addFloat", &pyConfig::addFloat )
        .def("addGroup", &pyConfig::addGroup )
        .def("addList", &pyConfig::addList )
        .def("addArray", &pyConfig::addArray )
        .def("addArray", &pyConfig::addArray_str )
        .def("setValue", &pyConfig::setValue_bool )
        .def("setValue", &pyConfig::setValue_float )
        .def("setValue", &pyConfig::setValue_double )
        .def("setValue", &pyConfig::setValue_longlong )
        .def("setValue", &pyConfig::setValue_long )
        .def("setValue", &pyConfig::setValue_int )
        .def("setValue", &pyConfig::setValue_str )
        .def("appendToList", &pyConfig::appendToList_Group )
        .def("appendToList", &pyConfig::appendToList_bool )
        .def("appendToList", &pyConfig::appendToList_float )
        .def("appendToList", &pyConfig::appendToList_double)
        .def("appendToList", &pyConfig::appendToList_longlong )
        .def("appendToList", &pyConfig::appendToList_long )
        .def("appendToList", &pyConfig::appendToList_int )
        .def("appendToList", &pyConfig::appendToList_str)
    ;
}
