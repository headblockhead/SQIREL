{ lib
, gcc
, gnumake
, cmake
, stdenv
, gcovr
}:

stdenv.mkDerivation {
  name = "squirrel-tests";
  src = ./.;

  nativeBuildInputs = [ cmake gnumake gcovr ];
  buildInputs = [ ];

  cmakeFlags = [
    "-DCMAKE_BUILD_TYPE=Testing"
    "-DCMAKE_C_COMPILER=${gcc}/bin/gcc"
    "-DCMAKE_CXX_COMPILER=${gcc}/bin/g++"
  ];

  installPhase = ''
    mkdir -p $out # Output directory must be created for the build to succeed
    ctest -T Test -T Coverage --timeout 60
  '';

  meta = with lib; {
    homepage = "https://github.com/headblockhead/squirrel";
    description = "Keyboard firmware library inspired by QMK.";
    platforms = with platforms; linux;
  };
}

