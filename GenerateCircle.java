
import java.awt.Toolkit;
import java.awt.datatransfer.Clipboard;
import java.awt.datatransfer.StringSelection;

class GenerateCircle {

    final static double PI = 3.14159265359;

    public static double[] generateCircleVertex(double x, double y, double z, double red, double green, double blue, double radiusX, double radiusY, int triangleAmount, double texCoordX, double texCoordY) {
        double[] res = new double[8 + (triangleAmount * 16)];
        double angleInc = (2 * PI) / triangleAmount; // 360 / amount of triangles
        double aheadAngle = angleInc; // for left vertex
        res[0] = x;
        res[1] = y;
        res[2] = z; // z
        res[3] = red; // r
        res[4] = green; // g
        res[5] = blue; // b
        res[6] = texCoordX;
        res[7] = texCoordY;
        for (int i = 8; i < res.length; i += 8) {
            res[i] = x + Math.cos(aheadAngle) * radiusX;
            res[i + 1] = y + Math.sin(aheadAngle) * radiusY;
            res[i + 2] = z; // z
            res[i + 3] = red; // r
            res[i + 4] = green; // g
            res[i + 5] = blue; // b
            res[i + 6] = texCoordX + Math.cos(aheadAngle) * radiusX;
            res[i + 7] = texCoordY + + Math.sin(aheadAngle) * radiusY;
            aheadAngle += angleInc;
        }
        return res;
    }

    // FROM: https://www.baeldung.com/java-clipboard-copy-paste-text
    public static void copyTextToClipboard(String text) {
        StringSelection stringSelection = new StringSelection(text);
        Clipboard clipboard = Toolkit.getDefaultToolkit().getSystemClipboard();
        clipboard.setContents(stringSelection, null);
    }

    public static void main(String[] args) {
        double x = 0.0;
        double y = 0.0;
        double z = -0.3;
        double red = 1.0;
        double green = 1.0;
        double blue = 1.0;
        double radiusX = 1.0;
        double radiusY = 1.0;
        int triangleAmount = 20; 
        double texCoordX = 0.0;
        double texCoordY = 0.0;
        double[] vertices = generateCircleVertex(x, y, z, red, green, blue, radiusX, radiusY, triangleAmount, texCoordX, texCoordY);
        // print
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < vertices.length; i += 8) {
            sb.append(vertices[i]).append("f, ")
                .append(vertices[i + 1]).append("f, ")
                .append(vertices[i + 2]).append("f, ")
                .append(vertices[i + 3]).append("f, ")
                .append(vertices[i + 4]).append("f, ")
                .append(vertices[i + 5]).append("f, ")
                .append(vertices[i + 6]).append("f, ")
                .append(vertices[i + 7]).append("f,");
            if (i + 8 < vertices.length - 1) {
                sb.append("\n");
            }
        }
        String content = sb.toString();
        try {
            copyTextToClipboard(content);
            System.out.println("Copied: " + content);
        } catch (Exception e) {
            System.err.println("Error: " + e.getMessage());
        }
    }
}
