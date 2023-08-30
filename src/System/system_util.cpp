#include "system_util.h"

#include "SD.h"

String system_util::uniquifyFilename(String filename) {
    while (SD.exists(filename)) {
        // find extension (example: myFile.csv)
        int extensionIndex = filename.lastIndexOf('.');
        String base = filename.substring(0, extensionIndex == -1 ? filename.length() : extensionIndex);
        String extension = extensionIndex == -1 ? "" : filename.substring(extensionIndex + 1);
        base.trim();
 
        // find current file count (example: myFile(2).csv)
        int fileCountStart = base.lastIndexOf('(');
        int fileCountEnd = base.lastIndexOf(')');
        int count = 0;
        if (fileCountStart != -1 && fileCountEnd != -1 && fileCountEnd == (int)base.length() - 1) {
            String countString = base.substring(fileCountStart + 1, fileCountEnd);
            bool numeric = true;
            
            // checks if all characters in countString are numeric
            for (size_t i = 0; i < countString.length(); i++) {
                if (!isdigit(countString.charAt(i))) {
                    numeric = false;
                    break;
                }
            }

            if (numeric) {
                count = countString.toInt();
                // take count out of file filename
                base = base.substring(0, fileCountStart);
                base.trim();
            }
        }
        filename = base + "(" + (count + 1) + ")" + (extension.equals("") ?  "" : "." + extension);
    }
    return filename;
}