#!/bin/sh

get_checksum() {
	local fn=$1
	echo "checkdum = $(shasum ${fn})"
}

# 1. Clean test area
rm -f data/*.geheim
rm -f clear_files.shasum

# 2. Gather checksums of data target files:
shasum data/* > clear_files.shasum

# 3. Gather test targets(in data/ sub-directory)
# Ensure the loop skips safely if no files match
shopt -s nullglob

# Populate the "array" from the subdirectory
echo "\n\033[32mCollecting target files:"
echo "------------------------\033[0m"
for FILE in data/*; do
	echo "$FILE"
	# Verify it is actually a file, not a directory
	if [[ -f "$FILE" && -e "$FILE" ]]; then
		FILES="$FILES $FILE"	#files="$files#$file"
	fi
done

# 4. Encode the files (file -> file.geheim):
echo "\n\033[32mEncode the files:"
echo "-----------------\033[0m"
OLDIFS="$IFS"
IFS=" "

for FILE in $FILES; do
	yes "SomeSecretPasscode" | geheim -e -f $FILE
done

# 5. Decode encode files (file.geheim -> file.geheim.geheim):
echo "\n\033[32mEncode the files:"
echo "-----------------\033[0m"

for FILE in $FILES; do
	ENCODED_FILE="$FILE.geheim"
	yes "SomeSecretPasscode" | geheim -f $ENCODED_FILE
done

# 6. Gathere the checksums of the encoded->decoded files:
echo "\n\033[32mChecking checksums of decoded files with the clear files:"
echo "---------------------------------------------------------\033[0m"

for FILE in $FILES; do
	DECODED_FILE="$FILE.geheim.geheim"
	# Extract just the hash field (removing the filename).
	LOCAL_HASH=$(shasum "$DECODED_FILE" | cut -d' ' -f1)

	# Check if the hash exists in the clear_files.shasum file.
	if grep -q "$LOCAL_HASH" clear_files.shasum; then
		echo "$DECODED_FILE: \033[32mOK\033[0m"
	else
		echo "$DECODED_FILE: \033[31mFAILED\033[0m"
	fi
done


# The file you want to test
#target_file="different_name.txt"

# 1. Calculate the hash of your local file
# Cut extracts just the hash field, removing the filename
#local_hash=$(shasum "$target_file" | cut -d' ' -f1)

# 2. Check if that hash exists inside your master checksum file
#if grep -q "$local_hash" hashes.txt; then
#    echo "$target_file: OK (Found matching hash in hashes.txt)"
#else
#    echo "$target_file: FAILED (No matching hash found)"
#    exit 1
#fi

# Format: echo "[HASH]  [NEW_FILENAME]" | shasum -c -
#echo "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855  different_name.txt" | shasum -c -

IFS="$OLDIFS"
