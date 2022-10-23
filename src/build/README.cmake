Notes for building QImageViewer and the "lena" test program with cmake.

% cd QImageViewer/src/build
% cmake -DCMAKE_BUILD_TYPE=Debug ..     # Debug release -g.
% cmake -DCMAKE_BUILD_TYPE=Release ..   # Optimized release -O.
% cmake -DCMAKE_CXX_FLAGS=-Wall ..      # With all compile warnings turned on.


% make clean                            # Clean files.
% sudo make install                     # Install it.

% cmake --build . --config Release
% sudo cmake --install .


