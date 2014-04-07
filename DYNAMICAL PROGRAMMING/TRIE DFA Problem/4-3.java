+import java.io.*;
+
+
 /**
  * User: dark
  * Date: 29.04.12
  * Time: 19:35
  */
 public class T3 {
+
+    public static byte[] readLowercaseCharsAsBytes(final InputStream input) throws IOException {
+        byte[] buffer = new byte[input.available()];
+        input.read(buffer, 0, buffer.length);
+        int i = 0;
+
+        while (buffer[i] >= 'a' && buffer[i] <= 'z' && i < buffer.length) {
+            ++i;
+        }
+        if (buffer.length != i) {
+            final byte[] tmp = new byte[i];
+            System.arraycopy(buffer, 0, tmp, 0, i);
+            buffer = tmp;
+        }
+        return buffer;
+    }
+
+    public static int[] zFunction(final byte[] string) {
+
+        final int[] result = new int[string.length];
+
+        for (int currentPosition = 1, leftBorder = 0, rightBorder = 0;
+             currentPosition <  string.length; ++currentPosition) {
+            if (currentPosition <= rightBorder) {
+                result[currentPosition] = Math.min(rightBorder - currentPosition + 1, result[currentPosition - leftBorder]);
+            }
+            while (currentPosition + result[currentPosition] <  string.length &&
+                   string[result[currentPosition]] == string[currentPosition + result[currentPosition]]) {
+                ++result[currentPosition];
+            }
+            if (currentPosition + result[currentPosition] - 1 > rightBorder) {
+                leftBorder = currentPosition;
+                rightBorder = currentPosition + result[currentPosition] - 1;
+            }
+        }
+        result[0] = string.length;
+        return result;
+    }
+
+    public static void printInArray(final int[] array, final PrintStream outputStream) {
+        final StringBuilder s = new StringBuilder();
+        s.append(array[0]);
+        for (int i = 1; i < array.length; i++) {
+            s.append(' ').append(array[i]);
+        }
+        s.append('\n');
+        outputStream.print(s.toString());
+    }
+
+    public static void main(final String[] args) throws IOException {
+        printInArray(zFunction(readLowercaseCharsAsBytes(System.in)), System.out);
+    }
 }
 