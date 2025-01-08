{
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-24.05";
    flake-utils.url = "github:numtide/flake-utils";
  };
  outputs = { nixpkgs, flake-utils, ... }:
    flake-utils.lib.eachDefaultSystem
      (system:
        let
          pkgs = import nixpkgs {
            inherit system;
          };
        in
        rec {
          devShells.default = pkgs.mkShell {
            buildInputs = with pkgs; [
              xc
              cmake
              gcovr
            ];
          };
          packages.squirrel = pkgs.stdenv.mkDerivation {
            name = "squirrel";
            src = ./.;

            nativeBuildInputs = with pkgs; [ cmake gcovr ];

            buildPhase = ''
              runHook preBuild
              cmake .
              cmake --build . -t squirrel
              runHook postBuild
            '';

            installPhase = ''
              runHook preInstall
              mkdir -p $out/lib
              mkdir -p $out/include/squirrel
              cp libsquirrel.a $out/lib/libsquirrel.a
              cp $src/include/* $out/include/squirrel
              runHook postInstall
            '';

            checkPhase = ''
              runHook preCheck
              cmake .
              cmake --build .
              cd tests
              ctest --timeout 60
              cd ..
              runHook postCheck
            '';
          };
          packages.default = packages.squirrel;
          checks.squirrel = packages.squirrel.overrideAttrs (oldAttrs: {
            doCheck = true;
          });
        }
      );
}
