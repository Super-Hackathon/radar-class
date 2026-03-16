#!/bin/bash

# ┌──────────────────────────────────────────────────────────────┐
# │           RADAR_CLASS folder refresh script                  │
# └──────────────────────────────────────────────────────────────┘

# === Configuration ===
SOURCE_DIR="/home/pi/Documents/BACKUP"
TARGET_DIR="/home/pi/Desktop/RADAR_CLASS"

# === Safety checks ===
if [ ! -d "$SOURCE_DIR" ]; then
    echo "ERROR: Source folder does not exist!"
    echo "       $SOURCE_DIR"
    exit 1
fi

if [ ! -d "$TARGET_DIR" ]; then
    echo "ERROR: Target folder does not exist!"
    echo "       $TARGET_DIR"
    echo "Creating it now..."
    mkdir -p "$TARGET_DIR"
fi

echo "This script will:"
echo "  1. DELETE all files and folders inside:"
echo "     $TARGET_DIR/"
echo "  2. COPY everything from:"
echo "     $SOURCE_DIR/"
echo ""
echo -n "Are you sure you want to continue? (y/N): "

read -r answer
if [[ ! "$answer" =~ ^[Yy]$ ]]; then
    echo "Aborted."
    exit 0
fi

echo ""
echo "→ Clearing target folder..."
# The /* is important — it deletes contents, not the folder itself
rm -rf "${TARGET_DIR:?}"/* "${TARGET_DIR:?}"/.*

# Some hidden files (.folder, .file) might still remain — second pass
# (the :? protects us if variable is empty/unset)
rm -rf "${TARGET_DIR:?}"/.*

echo "→ Copying new files..."
cp -r "$SOURCE_DIR"/*     "$TARGET_DIR"/ 2>/dev/null
cp -r "$SOURCE_DIR"/.*     "$TARGET_DIR"/ 2>/dev/null

echo ""
echo "Done."
echo "Target folder now contains files from BACKUP."
echo ""
ls -la "$TARGET_DIR" | head -n 15
echo "   ... (showing first 15 lines)"