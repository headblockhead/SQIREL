{ pkgs ? import <nixpkgs> { } }:
let
  xc = pkgs.buildGoModule rec {
    pname = "xc";
    version = "0655cccfcf036556aeaddfb8f45dc7e8dd1b3680";
    subPackages = [ "cmd/xc" ];
    src = pkgs.fetchFromGitHub {
      owner = "joerdav";
      repo = "xc";
      rev = version;
      sha256 = "kCcCqqwvjN07H8FPG4tXsRVRcMqT8dUNt9pwW1kKAe8=";
    };
    vendorSha256 = "AwlXX79L69dv6wbFtlbHAeZRuOeDy/r6KSiWwjoIgWw=";
  };
in
pkgs.mkShell {
  # nativeBuildInputs is usually what you want -- tools you need to run
  nativeBuildInputs = with pkgs.buildPackages; [
    cmake
    gcc
    ccls
    python39
    gnumake
    git
    cacert
    xc
  ];

}
