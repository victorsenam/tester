Just some helper scripts.

# decompress.sh
Sends every compressed file (.zip, .tar, .tar.gz) or not (.java) on `safebatch/` to `result/` uncompressed and keeps the fails on `batch/`.

# commentToGrades.sh
Visits every folder on `result/` and concatenates `comment.txt`, `judge.log` and `judge.out` on a single named file on `grades/`.

# gradesToClipboard.sh
Iterates files on `grades/` copying them to the clipboard.
