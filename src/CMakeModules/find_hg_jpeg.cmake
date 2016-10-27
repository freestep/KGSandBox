
SET(JPEG_DIR "" CACHE PATH "Set to base JPEG install path")
MACRO( FIND_JPEG_INCLUDE THIS_JPEG_INCLUDE_DIR THIS_JPEG_INCLUDE_FILE )

FIND_PATH( ${THIS_JPEG_INCLUDE_DIR} ${THIS_JPEG_INCLUDE_FILE}
    PATHS
        ${JPEG_DIR}
        $ENV{JPEG_SOURCE_DIR}
        $ENV{JPEGDIR}
        $ENV{JPEG_DIR}
        /usr/local/
        /usr/
        /sw/ # Fink
        /opt/local/ # DarwinPorts
        /opt/csw/ # Blastwave
        /opt/
        [HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Control\\Session\ Manager\\Environment;JPEG_ROOT]/
        ~/Library/Frameworks
        /Library/Frameworks
    PATH_SUFFIXES
        /include/
)

ENDMACRO( FIND_JPEG_INCLUDE THIS_JPEG_INCLUDE_DIR THIS_JPEG_INCLUDE_FILE )

FIND_JPEG_INCLUDE( JPEG_INCLUDE_DIR       JPEG/Configurator.hh )

###### libraries ######

MACRO( FIND_JPEG_LIBRARY MYLIBRARY MYLIBRARYNAME )

FIND_LIBRARY(${MYLIBRARY}
    NAMES
        ${MYLIBRARYNAME}
    PATHS
        ${JPEG_DIR}
        $ENV{JPEG_BUILD_DIR}
        $ENV{JPEG_DIR}
        $ENV{JPEGDIR}
        ~/Library/Frameworks
        /Library/Frameworks
        /usr/local
        /usr
        /sw
        /opt/local
        /opt/csw
        /opt
        [HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Control\\Session\ Manager\\Environment;JPEG_ROOT]/lib
        /usr/freeware
    PATH_SUFFIXES
        /lib/
        /lib64/
        /build/lib/
        /build/lib64/
        /Build/lib/
        /Build/lib64/
     )

ENDMACRO(FIND_JPEG_LIBRARY LIBRARY LIBRARYNAME)

FIND_JPEG_LIBRARY( JPEG_DEBUG_LIBRARIES jpegD)



FIND_JPEG_LIBRARY( JPEG_RELEASE_LIBRARIES jpeg)



SET( JPEG_FOUND "NO" )
IF( JPEG_LIBRARY AND JPEG_INCLUDE_DIR )
    SET( JPEG_FOUND "YES" )
    SET( JPEG_INCLUDE_DIRS ${JPEG_INCLUDE_DIR})
    GET_FILENAME_COMPONENT( JPEG_LIBRARIES_DIR ${JPEG_LIBRARY} PATH )
ENDIF( JPEG_LIBRARY AND JPEG_INCLUDE_DIR )


