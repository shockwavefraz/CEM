#get the current directory
THIS_SCRIPT="${BASH_SOURCE[0]}"
while([ -h "${THIS_SCRIPT}" ]) do 
  THIS_SCRIPT="$(readlink "$THIS_SCRIPT")"
done

#define the project root and the tool chains directory
PROJECT_ROOT="$(cd -P "$(dirname "$THIS_SCRIPT")" && pwd)"
TOOLCHAINS_DIR="${PROJECT_ROOT}/CMakeToolChains"

echo "Project Root Directory: ${PROJECT_ROOT}"

#-------------------------------------------
printHelp() {

    cat<<EOF

    Usage: generate build files, provides the following options:

    -X|--use-xcode: builds XCode project files (default is Unix Makefiles)
    -c|--clean-build-directory: deletes the current build directory before generating new files (this option must be selected in order to switch generators)
    -m|--mode: Selects the mode to build (can be Debug or Release, defaults to Release)
    -p|--enable-profiling:
    --disable-memcheck: Disables Running Google Perftools Memory Check
    -h|--help: print this menu

EOF
    }

#-------------------------------------------

#initialize flags
BUILD_MODE=Release
CLEAN_BUILD_DIRECTORY=0
CMAKE_ARGS=
RUN_MEMCHECK=1
RUN_VALGRIND=1
TOOLCHAIN=clang-64

#loop over input to set flags
for i in "$@"
do 
case $i in

	-h|--help)
	    printHelp
	    exit -1
	;;
	
	-m|--mode)
	    shift
	BUILD_MODE=$1
	echo "BUILD_MODE = $1"
	shift
	;;
	
	-p|--enable-profiling)
	    CMAKE_ARGS="${CMAKE_ARGS} -C${TOOLCHAINS_DIR}/profiler.cmake"
	    shift
	;;
	
	--disable-valgrind)
		RUN_VALGRIND=0
		shift
		;;
		
	--disable-memcheck)
	    RUN_MEMCHECK=0
	    shift
	;;
	
	-X|--use-xcode)
	    CMAKE_ARGS="${CMAKE_ARGS} -G Xcode"
	    TOOLCHAIN=xcode
	    shift
	;;
	
	-c|--clean-build-directory)
	    CLEAN_BUILD_DIRECTORY=1
	    shift
	;;
		
	-?*)
	echo "ERROR: Unknown Option $1"
	printHelp
	exit -1
	;;
	
         --)
       shift
        while [ "$1" != ""];do
    	 CMAKE_ARGS = "{CMAKE_ARGS} $1"
	 echo "CMAKE_ARGS = {CMAKE_ARGS} $1"
    	 shift
        done
    ;;  	
esac
done

#check the arguments
if [[ "${BUILD_MODE}" != "Debug" && "${BUILD_MODE}" != "Release" ]]; then
	echo "ERROR: Unknown Build Mode: ${BUILD_MODE}"
	printHelp
	exit -1
fi

if [ ${RUN_MEMCHECK} -eq 1 ]; then
    CMAKE_ARGS="${CMAKE_ARGS} -DRUN_MEMCHECK=ON"
fi
   
if [ ${RUN_VALGRIND} -eq 1 ]; then
    CMAKE_ARGS="${CMAKE_ARGS} -DRUN_VALGRIND=ON"
fi
      
#output the toolchain info
echo "Configuring ${BUILD_MODE} mode"
if [ "$CMAKE_ARGS" != "" ]; then
	echo "Additional CMake Arguments: ${CMAKE_ARGS}"
fi

if [ $CLEAN_BUILD_DIRECTORY -eq 1 ]; then
		echo "Cleaning up the directories"
	if [ -d ${PROJECT_ROOT}/build ]; then
    	echo "Cleaning the build directory"
		rm -rf ${PROJECT_ROOT}/build
	fi
	
	if [ -d ${PROJECT_ROOT}/bin ]; then
    	echo "Cleaning the bin directory"
		rm -rf ${PROJECT_ROOT}/bin
	fi
	
	if [ -d ${PROJECT_ROOT}/docs ]; then
    	echo "Cleaning the docs directory"
		rm -rf ${PROJECT_ROOT}/docs
	fi
fi

#create the build directory if it doesn't already exist
if ! [ -d ${PROJECT_ROOT}/build ]; then
	mkdir ${PROJECT_ROOT}/build
fi

#create the toolchain directory if it doesn't already exist
if ! [ -d ${PROJECT_ROOT}/build/${TOOLCHAIN} ]; then
	mkdir ${PROJECT_ROOT}/build/${TOOLCHAIN}
fi

#create the build mode if it doesn't already exist
if ! [ -d ${PROJECT_ROOT}/build/${TOOLCHAIN}/${BUILD_MODE} ]; then
	mkdir ${PROJECT_ROOT}/build/${TOOLCHAIN}/${BUILD_MODE}
fi

#set up the build directory and CMake root directory
BUILD_DIR="${PROJECT_ROOT}/build/${TOOLCHAIN}/${BUILD_MODE}"
CMAKE_ROOT_DIR="${PROJECT_ROOT}/trunk"

echo "cd to ${BUILD_DIR}"
cd "${BUILD_DIR}"

#add the mode
CMAKE_ARGS="${CMAKE_ARGS} -DCMAKE_BUILD_TYPE=${BUILD_MODE}"

#run cmake
echo "Executing CMake command: cmake ${CMAKE_ROOT_DIR} ${CMAKE_ARGS}"
cmake ${CMAKE_ROOT_DIR} ${CMAKE_ARGS}
