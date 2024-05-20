{ lib
, llvmPackages_11
, cmake
, gcc
}:

llvmPackages_11.stdenv.mkDerivation {
  pname = "SQUIRREL";
  version = "0.0.0";

  src = ./.;

  nativeBuildInputs = [ cmake gcc ];

  installPhase = ''
    mkdir -p $out
    cp -r . $out
  '';

  meta = with lib; {
    homepage = "https://github.com/headblockhead/SQUIRREL";
    description = ''Simplified, runtime-configurable QMK as a library'';
    licencse = licenses.gpl3;
    platforms = with platforms; linux;
    maintainers = [ maintainers.headblockhead ];
  };
}
