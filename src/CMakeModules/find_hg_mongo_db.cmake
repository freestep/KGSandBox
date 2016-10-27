
SET(MONGODB_DIR "" CACHE PATH "Set to base MONGODB install path")
MACRO( FIND_MONGODB_INCLUDE THIS_MONGODB_INCLUDE_DIR THIS_MONGODB_INCLUDE_FILE )

FIND_PATH( ${THIS_MONGODB_INCLUDE_DIR} ${THIS_MONGODB_INCLUDE_FILE}
    PATHS
        ${MONGODB_DIR}
        $ENV{MONGODB_SOURCE_DIR}
        $ENV{MONGODBDIR}
        $ENV{MONGODB_DIR}
        /usr/local/
        /usr/
        /sw/ # Fink
        /opt/local/ # DarwinPorts
        /opt/csw/ # Blastwave
        /opt/
        [HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Control\\Session\ Manager\\Environment;MONGODB_ROOT]/
        ~/Library/Frameworks
        /Library/Frameworks
    PATH_SUFFIXES
        /include/
)

ENDMACRO( FIND_MONGODB_INCLUDE THIS_MONGODB_INCLUDE_DIR THIS_MONGODB_INCLUDE_FILE )

FIND_MONGODB_INCLUDE( MONGODB_INCLUDE_DIR      mongo/pch.h )

###### libraries ######

MACRO( FIND_MONGODB_LIBRARY MYLIBRARY MYLIBRARYNAME )

FIND_LIBRARY(${MYLIBRARY}
    NAMES
        ${MYLIBRARYNAME}
    PATHS
        ${MONGODB_DIR}
        $ENV{MONGODB_BUILD_DIR}
        $ENV{MONGODB_DIR}
        $ENV{MONGODBDIR}
        ~/Library/Frameworks
        /Library/Frameworks
        /usr/local
        /usr
        /sw
        /opt/local
        /opt/csw
        /opt
        [HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Control\\Session\ Manager\\Environment;MONGODB_ROOT]/lib
        /usr/freeware
    PATH_SUFFIXES
        /lib/
        /lib64/
        /build/lib/
        /build/lib64/
        /Build/lib/
        /Build/lib64/
     )

ENDMACRO(FIND_MONGODB_LIBRARY LIBRARY LIBRARYNAME)

FIND_MONGODB_LIBRARY( mogoDB_DEBUG_LIBRARIES mongoclientd)



FIND_MONGODB_LIBRARY( mogoDB_RELEASE_LIBRARIES mongoclient)



SET( MONGODB_FOUND "NO" )
IF( MONGODB_LIBRARY AND MONGODB_INCLUDE_DIR )
    SET( MONGODB_FOUND "YES" )
    SET( MONGODB_INCLUDE_DIRS ${MONGODB_INCLUDE_DIR})
    GET_FILENAME_COMPONENT( MONGODB_LIBRARIES_DIR ${MONGODB_LIBRARY} PATH )
ENDIF( MONGODB_LIBRARY AND MONGODB_INCLUDE_DIR )


