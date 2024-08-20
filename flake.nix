{
  description = "Tools for developing, building and testing SQUIRREL";
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-24.05";
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
                picotool = pkgs.callPackage ./picotool.nix {
                  pico-sdk = pkgs.callPackage ./pico-sdk.nix { };
                };
                pico-sdk = pkgs.callPackage ./pico-sdk.nix { };
              })
            ];
          };
        in
        {
          # Development shell (nix develop)
          devShells.default = pkgs.mkShell {
            buildInputs = with pkgs; [
              xc
              gcovr
              cmake
              gcc
              ccls
              gnumake
              git
              cacert
            ];
          };
          # The firmware (nix build)
          packages.squirrel = pkgs.callPackage ./default.nix { };
          checks.squirrel-tests = pkgs.callPackage ./tests.nix { };
        }
      );
}
