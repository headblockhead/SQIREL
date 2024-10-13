{
  description = "Tools for developing, building and testing SQUIRREL";
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
          # The library (nix build)
          packages.squirrel = pkgs.callPackage ./default.nix { };
          # The tests (nix flake check)
          checks.squirrel-tests = pkgs.callPackage ./tests.nix { };
        }
      );
}
