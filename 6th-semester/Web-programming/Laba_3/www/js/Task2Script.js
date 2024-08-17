var str, sel, n = 8, i, j;
document.write("<table>");
for (i = 0; i < n; i++) {
    document.write("<tr>");
    for (j = 0; j < n; j++) {
        sel = (i + j) % 2;
        if (sel == 0) {
            str = "class='r1'";
        } else {
            str = "class='r2'";
        }
        if (i <= 2 && ((i % 2 == 0 && j % 2 == 1) || (i % 2 == 1 && j % 2 == 0))) {
            document.write("<td " + str + "><div class='circle_black'></div></td>");
        } else if (i >= 5 && ((i % 2 == 1 && j % 2 == 0) || (i % 2 == 0 && j % 2 == 1))) {
            document.write("<td " + str + "><div class='circle_white'></div></td>");
        } else {
            document.write("<td " + str + "></td>");
        }
    }
    document.write("</tr>");
}
document.write("</table>");