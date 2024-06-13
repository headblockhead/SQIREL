{
  description = "Tools for developing and building SQUIRREL";
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-23.11";
    flake-utils.url = "github:numtide/flake-utils";
    xc.url = "github:joerdav/xc";
  };
  outputs = { self, nixpkgs, flake-utils, ... }@inputs:
    flake-utils.lib.eachDefaultSystem
      (system:
        let
          pkgs = import nixpkgs {
            inherit system;
            overlays = [
              (final: prev: {
                xc = inputs.xc.packages.x86_64-linux.xc;
              })
            ];
          };
        in
        {
          packages.default = pkgs.callPackage ./default.nix { };
          devShells.default = pkgs.mkShell {
            buildInputs = [
              inputs.xc

              pkgs.cmake
              pkgs.gcc
              pkgs.ccls
              pkgs.python39
              pkgs.gnumake
              pkgs.git
              pkgs.cacert
            ];
          };
        }
      );
}
