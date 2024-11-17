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
          # The library (nix build)
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
              cp libsquirrel.a $out/lib/libsquirrel.a
              runHook postInstall
            '';

            checkPhase = ''
              runHook preCheck
              cmake .
              cmake --build .
              ctest --timeout 60
              runHook postCheck
            '';
          };

          checks.squirrel = packages.squirrel.overrideAttrs (oldAttrs: {
            doCheck = true;
          });
        }
      );
}
