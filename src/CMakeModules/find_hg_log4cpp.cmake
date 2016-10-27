
SET(LOG4CPP_DIR "" CACHE PATH "Set to base LOG4CPP install path")
MACRO( FIND_LOG4CPP_INCLUDE THIS_LOG4CPP_INCLUDE_DIR THIS_LOG4CPP_INCLUDE_FILE )

FIND_PATH( ${THIS_LOG4CPP_INCLUDE_DIR} ${THIS_LOG4CPP_INCLUDE_FILE}
    PATHS
        ${LOG4CPP_DIR}
        $ENV{LOG4CPP_SOURCE_DIR}
        $ENV{LOG4CPPDIR}
        $ENV{LOG4CPP_DIR}
        /usr/local/
        /usr/
        /sw/ # Fink
        /opt/local/ # DarwinPorts
        /opt/csw/ # Blastwave
        /opt/
        [HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Control\\Session\ Manager\\Environment;LOG4CPP_ROOT]/
        ~/Library/Frameworks
        /Library/Frameworks
    PATH_SUFFIXES
        /include/
)

ENDMACRO( FIND_LOG4CPP_INCLUDE THIS_LOG4CPP_INCLUDE_DIR THIS_LOG4CPP_INCLUDE_FILE )

FIND_LOG4CPP_INCLUDE( LOG4CPP_INCLUDE_DIR       log4cpp/Configurator.hh )

###### libraries ######

MACRO( FIND_LOG4CPP_LIBRARY MYLIBRARY MYLIBRARYNAME )

FIND_LIBRARY(${MYLIBRARY}
    NAMES
        ${MYLIBRARYNAME}
    PATHS
        ${LOG4CPP_DIR}
        $ENV{LOG4CPP_BUILD_DIR}
        $ENV{LOG4CPP_DIR}
        $ENV{LOG4CPPDIR}
        ~/Library/Frameworks
        /Library/Frameworks
        /usr/local
        /usr
        /sw
        /opt/local
        /opt/csw
        /opt
        [HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Control\\Session\ Manager\\Environment;LOG4CPP_ROOT]/lib
        /usr/freeware
    PATH_SUFFIXES
        /lib/
        /lib64/
        /build/lib/
        /build/lib64/
        /Build/lib/
        /Build/lib64/
     )

ENDMACRO(FIND_LOG4CPP_LIBRARY LIBRARY LIBRARYNAME)

FIND_LOG4CPP_LIBRARY( log4Cpp_DEBUG_LIBRARIES log4cppd)



FIND_LOG4CPP_LIBRARY( log4Cpp_RELEASE_LIBRARIES log4cpp)



SET( LOG4CPP_FOUND "NO" )
IF( LOG4CPP_LIBRARY AND LOG4CPP_INCLUDE_DIR )
    SET( LOG4CPP_FOUND "YES" )
    SET( LOG4CPP_INCLUDE_DIRS ${LOG4CPP_INCLUDE_DIR})
    GET_FILENAME_COMPONENT( LOG4CPP_LIBRARIES_DIR ${LOG4CPP_LIBRARY} PATH )
ENDIF( LOG4CPP_LIBRARY AND LOG4CPP_INCLUDE_DIR )


