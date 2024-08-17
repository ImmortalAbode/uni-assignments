<%@page contentType="text/html" pageEncoding="UTF-8"%>
<jsp:useBean id="bean" scope="session" class="beans_jsp.MainBean"/>
<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <title>Финишная страница</title>
        <style>
            .error-message {
                color: red;
            }
        </style>
    </head>
    <body>
        <%
            String numbers = bean.getNumbers();
            String errorMessage = bean.getErrorMessage();
            String[] numbersArray = null;
            if (numbers != null && !numbers.isEmpty()) {
                numbersArray = numbers.split("\\s+");
            }
        %>
        <table style="border:1px solid black; font-size: 16px;">
            <%if (errorMessage != null && !errorMessage.isEmpty()) { %>
            <tr>
                <td style="border:1px solid black;" class="error-message"><%= errorMessage %></td>
            </tr>
            <%} else if (numbersArray != null) { %>
            <tr>
                <td style="border:1px solid black;">Ввели:</td>
                <%for (String num : numbersArray) { %>
                    <td style="border:1px solid black;"><%= num %></td>
                <%
                    }
                %>
            </tr>
            <tr>
                <td style="border:1px solid black;">Сумма отрицательных четных чисел:</td>
                <td style="border:1px solid black;"><%= bean.getEvenNegativeSum() %></td>
            </tr>
            <tr>
                <td style="border:1px solid black;">Сумма положительных нечетных чисел:</td>
                <td style="border:1px solid black;"><%= bean.getOddPositiveSum() %></td>
            </tr>
            <%
                }
            %>
        </table>
        <a href="MainPage.jsp?fromFinishPage=true">Возврат</a>
    </body>
</html>