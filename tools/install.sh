relative_root_dir=""
with_asset_bundler=false
build_type="Release"

while [[ "$#" -gt 0 ]]; do
  case $1 in
    -r|--root) relative_root_dir="$2"; shift ;;
    -b|--build-type) build_type="$2"; shift ;;
    -w|--with-asset-bundler) with_asset_bundler=true; shift ;;
    *) echo "Unknown parameter passed: $1"; exit 1 ;;
  esac
  shift
done

echo "Operating System: $os"
echo "Build type: $build_type"

if [[ $with_asset_bundler ]]; then
  ./install-asset-bundler.sh -r $relative_root_dir -b $build_type
  ./run-asset-bundler.sh -r $relative_root_dir -b $build_type
fi

./install-game.sh -r $relative_root_dir -b $build_type
