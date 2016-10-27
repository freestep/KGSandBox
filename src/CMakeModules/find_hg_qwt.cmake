
SET(QWT_DIR "" CACHE PATH "Set to base QWT install path")
MACRO( FIND_QWT_INCLUDE THIS_QWT_INCLUDE_DIR THIS_QWT_INCLUDE_FILE )

FIND_PATH( ${THIS_QWT_INCLUDE_DIR} ${THIS_QWT_INCLUDE_FILE}
    PATHS
        ${QWT_DIR}
        $ENV{QWT_SOURCE_DIR}
        $ENV{QWTDIR}
        $ENV{QWT_DIR}
        /usr/local/
        /usr/
        /sw/ # Fink
        /opt/local/ # DarwinPorts
        /opt/csw/ # Blastwave
        /opt/
        [HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Control\\Session\ Manager\\Environment;QWT_ROOT]/
        ~/Library/Frameworks
        /Library/Frameworks
    PATH_SUFFIXES
        /include/
)

ENDMACRO( FIND_QWT_INCLUDE THIS_QWT_INCLUDE_DIR THIS_QWT_INCLUDE_FILE )

FIND_QWT_INCLUDE( QWT_INCLUDE_DIR      qwt/qwt.h )

###### libraries ######

MACRO( FIND_QWT_LIBRARY MYLIBRARY MYLIBRARYNAME )

FIND_LIBRARY(${MYLIBRARY}
    NAMES
        ${MYLIBRARYNAME}
    PATHS
        ${QWT_DIR}
        $ENV{QWT_BUILD_DIR}
        $ENV{QWT_DIR}
        $ENV{QWTDIR}
        ~/Library/Frameworks
        /Library/Frameworks
        /usr/local
        /usr
        /sw
        /opt/local
        /opt/csw
        /opt
        [HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Control\\Session\ Manager\\Environment;QWT_ROOT]/lib
        /usr/freeware
    PATH_SUFFIXES
        /lib/
        /lib64/
        /build/lib/
        /build/lib64/
        /Build/lib/
        /Build/lib64/
     )

ENDMACRO(FIND_QWT_LIBRARY LIBRARY LIBRARYNAME)

if(UNIX)
	FIND_QWT_LIBRARY( QWT_DEBUG_LIBRARIES qwt)
else()
	FIND_QWT_LIBRARY( QWT_DEBUG_LIBRARIES qwtd)
endif()



FIND_QWT_LIBRARY( QWT_RELEASE_LIBRARIES qwt)



SET( QWT_FOUND "NO" )
IF( QWT_LIBRARY AND QWT_INCLUDE_DIR )
    SET( QWT_FOUND "YES" )
    SET( QWT_INCLUDE_DIRS ${QWT_INCLUDE_DIR})
    GET_FILENAME_COMPONENT( QWT_LIBRARIES_DIR ${QWT_LIBRARY} PATH )
ENDIF( QWT_LIBRARY AND QWT_INCLUDE_DIR )


