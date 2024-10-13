{ lib
, gcc
, gnumake
, cmake
, stdenv
}:

stdenv.mkDerivation {
  pname = "squirrel";
  version = "0.0.0";

  src = ./.;

  nativeBuildInputs = [ cmake gnumake ];
  buildInputs = [ ];

  cmakeFlags = [
    "-DCMAKE_BUILD_TYPE=Release"
    "-DCMAKE_C_COMPILER=${gcc}/bin/gcc"
    "-DCMAKE_CXX_COMPILER=${gcc}/bin/g++"
  ];

  installPhase = ''
    mkdir -p $out
    mkdir -p $out/lib
    cp libsquirrel.a $out/lib/libsquirrel.a
  '';

  checkPhase = ''make -C ./build test'';

  meta = with lib; {
    homepage = "https://github.com/headblockhead/squirrel";
    description = "Keyboard firmware library inspired by QMK.";
    licencse = licenses.mit;
    platforms = with platforms; linux;
  };
}

