{ lib
, gcc
, gnumake
, cmake
, stdenv
}:

stdenv.mkDerivation {
  pname = "squirrel-tests";
  version = "0.0.0";

  src = ./.;

  nativeBuildInputs = [ cmake gnumake ];
  buildInputs = [ ];

  cmakeFlags = [
    "-DCMAKE_BUILD_TYPE=Testing"
    "-DCMAKE_C_COMPILER=${gcc}/bin/gcc"
    "-DCMAKE_CXX_COMPILER=${gcc}/bin/g++"
  ];

  installPhase = ''
    cd tests
    ctest --timeout 60 # tests should never take longer than 60 seconds each to complete.
    cp -r . $out'';

  meta = with lib; {
    homepage = "https://github.com/headblockhead/squirrel";
    description = "Keyboard firmware library inspired by QMK.";
    licencse = licenses.mit;
    platforms = with platforms; linux;
  };
}

