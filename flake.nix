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
          # Reminder! If you want to use SQUIRREL as a library in one of your projects, you MUST build it yourself by adding the directory to your project with CMAKE and changing SQUIRREL_KEYCOUNT, for example:
          # add_compile_definitions(SQUIRREL_KEYCOUNT=100)
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
