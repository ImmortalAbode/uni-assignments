/*---------------------------
 |   ЗАДАНИЕ 1 (ГРАФИК)     |
 *--------------------------*/
//Определение URL-параметров.
function getUrlParameter(sParam) {
    const sPageURL = decodeURIComponent(window.location.search.substring(1));
    const sURLVariables = sPageURL.split('&');
    for (let i = 0; i < sURLVariables.length; i++) {
        const sParameterName = sURLVariables[i].split('=');
        if (sParameterName[0] === sParam) {
            return sParameterName[1] === undefined ? false : sParameterName[1];
        }
    }
    return false;
}
//Считывание URL-параметров.
var dx = getUrlParameter("dx"); //смещение графика по оси X
var dy = getUrlParameter("dy"); //смещение графика по оси Y
var k = getUrlParameter("k"); //изменение масштаба графика
//Заданная функция.
function myfunc(x) {
    return Math.sin(x) * Math.sin(x);
}
//Отрисовка графика.
function draw_graph(dx, dy, midX, midY) {
    var xstr = "";
    var xstr0 = "<div class='dot' style='background-color: blue;";
    var cur_x = -midX - 20 * dx * k;
    while (cur_x <= midX - 20 * dx * k) {
        var cur_y = myfunc(cur_x / 20 / k);
        if (20 * (-dy - cur_y) * k + midY >= 0 && 20 * (-dy - cur_y) * k + midY <= midY * 2) {
            xstr += xstr0 + "margin-left:" + (20 * dx * k + cur_x + midX) + "px;margin-top:" + ((20 * (-dy - cur_y) * k + midY)) + "px'></div>";
        }
        cur_x += 0.1;
    }
    document.getElementById('graph').innerHTML += xstr;
    //доделать масштаб
}
//Отрисовка вертикальной оси.
function vertical_line(x, y1, y2) {
    var ystr = "";
    var ystr0 = "<div class='dot' style='";
    var y = y1;
    ystr += ystr0 + "background-color: #129d43; margin-top:" + (y - 8) + "px;margin-left:" + (x - 4) + "px; font-size: 10px'>&#9650</div>";
    y -= 2;
    while (y <= y2) {
        ystr += ystr0 + "margin-top:" + y + "px;margin-left:" + x + "px'></div>";
        y++;
    }
    document.getElementById('graph').innerHTML += ystr;
}
//Отрисовка горизонтальной оси.
function horizontal_line(x1, x2, y) {
    var xstr = "";
    var xstr0 = "<div class='dot' style='";
    var x = x1;
    while (x <= x2) {
        if (x == (x2 - x1) / 2) {
            xstr += xstr0 + "background-color: white; margin-top:" + (y + 4) + "px;margin-left:" + (x + 4) + "px'>0</div>";
        }
        else {
            xstr += xstr0 + "margin-top:" + y + "px;margin-left:" + x + "px'></div>";
        }
        x++;
    }
    xstr += xstr0 + "background-color: #129d43; margin-top:" + (y - 4) + "px;margin-left:" + (x2 + 1) + "px'>&#9658</div>";
    document.getElementById('graph').innerHTML += xstr;
}
//Отрисовка осей, паралльльных горизонтальной оси.
function additional_horizontal_axes(midX, midY, step) {
    var cur_y_up = midY - 20 * k, cur_y_down = midY + 20 * k;
    var xstr = "";
    var xstr0 = "<div class='dot' style='";
    while (cur_y_up >= 0) {
        var cur_point_x = 0;
        while (cur_point_x <= midX * 2) {
            if (cur_point_x - 5 == midX) {
                xstr += xstr0 + "background-color: gray; width: 1px; height: 1px; margin-top:" + cur_y_up + "px;margin-left:" + cur_point_x + "px'>" + step + "</div>";
                step += 1;
            }
            else if (cur_point_x + 2 == midX || cur_point_x + 1 == midX || cur_point_x == midX || cur_point_x - 1 == midX || cur_point_x - 2 == midX) {
                xstr += xstr0 + "margin-top:" + cur_y_up + "px;margin-left:" + cur_point_x + "px'></div>";
            }
            else {
                xstr += xstr0 + "background-color: gray; width: 1px; height: 1px; margin-top:" + cur_y_up + "px;margin-left:" + cur_point_x + "px'></div>";
            }
            cur_point_x++;
        }
        cur_y_up -= 20 * k;
    }
    step = 1;
    while (cur_y_down <= midY * 2) {
        var cur_point_x = 0;
        while (cur_point_x <= midX * 2) {
            if (cur_point_x - 5 == midX) {
                xstr += xstr0 + "background-color: gray; width: 1px; height: 1px; margin-top:" + cur_y_down + "px;margin-left:" + cur_point_x + "px'>" + step + "</div>";
                step += 1;
            }
            else if (cur_point_x + 2 == midX || cur_point_x + 1 == midX || cur_point_x == midX || cur_point_x - 1 == midX || cur_point_x - 2 == midX) {
                xstr += xstr0 + "margin-top:" + cur_y_down + "px;margin-left:" + cur_point_x + "px'></div>";
            }
            else {
                xstr += xstr0 + "background-color: gray; width: 1px; height: 1px; margin-top:" + cur_y_down + "px;margin-left:" + cur_point_x + "px'></div>";
            }
            cur_point_x++;
        }
        cur_y_down += 20 * k;
    }
    step = 1;
    document.getElementById('graph').innerHTML += xstr;
}
//Отрисовка осей, параллельных вертикальной оси.
function additional_vertical_axes(midX, midY, step, newstep) {
    var cur_x_left = midX - 20 * k, cur_x_right = midX + 20 * k;
    var ystr = "";
    var ystr0 = "<div class='dot' style='";
    while (cur_x_right <= midX * 2) {
        var cur_point_y = 0;
        while (cur_point_y <= midY * 2) {
            if (cur_point_y - 5 == midY) {
                ystr += ystr0 + "background-color: gray; width: 1px; height: 1px; margin-top:" + cur_point_y + "px;margin-left:" + cur_x_right + "px'>" + step + "</div>";
                step += 1;
            }
            else if (cur_point_y + 2 == midY || cur_point_y + 1 == midY || cur_point_y == midY || cur_point_y - 1 == midY || cur_point_y - 2 == midY) {
                ystr += ystr0 + "margin-top:" + cur_point_y + "px;margin-left:" + cur_x_right + "px'></div>";
            }
            else {
                ystr += ystr0 + "background-color: gray; width: 1px; height: 1px; margin-top:" + cur_point_y + "px;margin-left:" + cur_x_right + "px'></div>";
            }
            cur_point_y++;
        }
        cur_x_right += 20 * k;
    }
    step = 1;
    while (cur_x_left >= 0) {
        var cur_point_y = 0;
        while (cur_point_y <= midY * 2) {
            if (cur_point_y - 5 == midY) {
                ystr += ystr0 + "background-color: gray; width: 1px; height: 1px; margin-top:" + cur_point_y + "px;margin-left:" + cur_x_left + "px'>" + step + "</div>";
                step += 1;
            }
            else if (cur_point_y + 2 == midY || cur_point_y + 1 == midY || cur_point_y == midY || cur_point_y - 1 == midY || cur_point_y - 2 == midY) {
                ystr += ystr0 + "margin-top:" + cur_point_y + "px;margin-left:" + cur_x_left + "px'></div>";
            }
            else {
                ystr += ystr0 + "background-color: gray; width: 1px; height: 1px; margin-top:" + cur_point_y + "px;margin-left:" + cur_x_left + "px'></div>";
            }
            cur_point_y++;
        }
        cur_x_left -= 20 * k;
    }
    document.getElementById('graph').innerHTML += ystr;
}
//Проверка URL-параметров.
function validateNumberFormat(number) {
    var regex = /^-?[0-9]\d*(\.\d*)?$/;
    return regex.test(number);
}
function checkURLParameters() {
    if (!dx) dx = 0;
    if (!dy) dy = 0;
    if (!k) k = 1;
    if (!validateNumberFormat(dx) || !validateNumberFormat(dy) || !validateNumberFormat(k)) {
        alert("Check that the number dx, dy and k is entered URL correctly and is a float or whole number.")
    }
    else {
        if (k < 1) {
            alert("There may be problems with displaying the graph. k set to 0.5, only this value, which is less than 1, is allowed. ")
            k = 0.5;
        }
        dx = Number(dx);
        dy = Number(dy);
        k = parseFloat(k);
    }
}
//Рисовка области графика.
function firstTask() {
    checkURLParameters();
    const graph = document.getElementById('graph');
    const information = document.getElementById('info');
    //Очищение поля для графика и информационного текста.
    graph.innerHTML = '';
    information.innerHTML = '';
    //Определение середины оси X и середины оси Y от размера поля графика.
    const graphWidth = graph.clientWidth;
    const graphHeight = graph.clientHeight;
    var midY = graphHeight / 2;
    var midX = graphWidth / 2;
    var step = 1;

    additional_horizontal_axes(midX, midY, step);
    additional_vertical_axes(midX, midY, step);
    horizontal_line(0, graphWidth, midY); //Рисуем ось X от точки (0; midY) до точки (graphWidth; midY)
    vertical_line(midX, 0, graphHeight); //Рисуем ось Y от точки (midX; 0) до точки (midX; graphHeight)
    draw_graph(dx, dy, midX, midY); //Рисуем график с возможным смещением (midX; midY).
    var infostr = "Смещение графика функции по оси X:" + dx + "<br />";
    infostr += "Смещение графика функции по оси Y:" + dy + "<br />";
    infostr += "Масштаб пропорциональности графика:" + k + "<br />";
    document.getElementById('info').innerHTML += infostr;
}
//Функция смещения вверх.
function up() {
    dy += 1;
    firstTask();
}
//Функция смещения вниз.
function down() {
    dy -= 1;
    firstTask();
}
//Функция смещения вправо.
function right() {
    dx += 1;
    firstTask();
}
//Функция смещения влево.
function left() {
    dx -= 1;
    firstTask();
}
//Функция увеличения масштаба.
function lower() {
    if (k > 1)
        k -= 1;
    firstTask();
}
//Функция уменьшения масштаба.
function upper() {
    if (k < 1)
        k = 1;
    else
        k += 1;
    firstTask();
}

/*---------------------------
 |   ЗАДАНИЕ 2 (ПОКЕР)      |
 *--------------------------*/
//Все карты колоды.
const cardImages = {
    'двойка_пики': 'images/cards/40px-Playing_card_spade_2.svg.png',
    'двойка_черви': 'images/cards/40px-Playing_card_heart_2.svg.png',
    'двойка_бубны': 'images/cards/40px-Playing_card_diamond_2.svg.png',
    'двойка_трефы': 'images/cards/40px-Playing_card_club_2.svg.png',
    'тройка_пики': 'images/cards/40px-Playing_card_spade_3.svg.png',
    'тройка_черви': 'images/cards/40px-Playing_card_heart_3.svg.png',
    'тройка_бубны': 'images/cards/40px-Playing_card_diamond_3.svg.png',
    'тройка_трефы': 'images/cards/40px-Playing_card_club_3.svg.png',
    'четверка_пики': 'images/cards/40px-Playing_card_spade_4.svg.png',
    'четверка_черви': 'images/cards/40px-Playing_card_heart_4.svg.png',
    'четверка_бубны': 'images/cards/40px-Playing_card_diamond_4.svg.png',
    'четверка_трефы': 'images/cards/40px-Playing_card_club_4.svg.png',
    'пятерка_пики': 'images/cards/40px-Playing_card_spade_5.svg.png',
    'пятерка_черви': 'images/cards/40px-Playing_card_heart_5.svg.png',
    'пятерка_бубны': 'images/cards/40px-Playing_card_diamond_5.svg.png',
    'пятерка_трефы': 'images/cards/40px-Playing_card_club_5.svg.png',
    'шестерка_пики': 'images/cards/40px-Playing_card_spade_6.svg.png',
    'шестерка_черви': 'images/cards/40px-Playing_card_heart_6.svg.png',
    'шестерка_бубны': 'images/cards/40px-Playing_card_diamond_6.svg.png',
    'шестерка_трефы': 'images/cards/40px-Playing_card_club_6.svg.png',
    'семерка_пики': 'images/cards/40px-Playing_card_spade_7.svg.png',
    'семерка_черви': 'images/cards/40px-Playing_card_heart_7.svg.png',
    'семерка_бубны': 'images/cards/40px-Playing_card_diamond_7.svg.png',
    'семерка_трефы': 'images/cards/40px-Playing_card_club_7.svg.png',
    'восьмерка_пики': 'images/cards/40px-Playing_card_spade_8.svg.png',
    'восьмерка_черви': 'images/cards/40px-Playing_card_heart_8.svg.png',
    'восьмерка_бубны': 'images/cards/40px-Playing_card_diamond_8.svg.png',
    'восьмерка_трефы': 'images/cards/40px-Playing_card_club_8.svg.png',
    'девятка_пики': 'images/cards/40px-Playing_card_spade_9.svg.png',
    'девятка_черви': 'images/cards/40px-Playing_card_heart_9.svg.png',
    'девятка_бубны': 'images/cards/40px-Playing_card_diamond_9.svg.png',
    'девятка_трефы': 'images/cards/40px-Playing_card_club_9.svg.png',
    'десятка_пики': 'images/cards/40px-Playing_card_spade_10.svg.png',
    'десятка_черви': 'images/cards/40px-Playing_card_heart_10.svg.png',
    'десятка_бубны': 'images/cards/40px-Playing_card_diamond_10.svg.png',
    'десятка_трефы': 'images/cards/40px-Playing_card_club_10.svg.png',
    'валет_пики': 'images/cards/40px-Playing_card_spade_J.svg.png',
    'валет_черви': 'images/cards/40px-Playing_card_heart_J.svg.png',
    'валет_бубны': 'images/cards/40px-Playing_card_diamond_J.svg.png',
    'валет_трефы': 'images/cards/40px-Playing_card_club_J.svg.png',
    'дама_пики': 'images/cards/40px-Playing_card_spade_Q.svg.png',
    'дама_черви': 'images/cards/40px-Playing_card_heart_Q.svg.png',
    'дама_бубны': 'images/cards/40px-Playing_card_diamond_Q.svg.png',
    'дама_трефы': 'images/cards/40px-Playing_card_club_Q.svg.png',
    'король_пики': 'images/cards/40px-Playing_card_spade_K.svg.png',
    'король_черви': 'images/cards/40px-Playing_card_heart_K.svg.png',
    'король_бубны': 'images/cards/40px-Playing_card_diamond_K.svg.png',
    'король_трефы': 'images/cards/40px-Playing_card_club_K.svg.png',
    'туз_пики': 'images/cards/40px-Playing_card_spade_A.svg.png',
    'туз_черви': 'images/cards/40px-Playing_card_heart_A.svg.png',
    'туз_бубны': 'images/cards/40px-Playing_card_diamond_A.svg.png',
    'туз_трефы': 'images/cards/40px-Playing_card_club_A.svg.png'
};
//Массив для хранения карт руки.
let hand = [];
//Проверяет, была ли такая карта уже добавлена в руку.
function isCardInHand(rank, suit) {
    for (const card of hand) {
        if (card.rank === rank && card.suit === suit) {
            return true;
        }
    }
    return false;
}
//Функция добавления карты.
function addCard() {
    const rank = document.getElementById('rank').value;
    const suit = document.getElementById('suit').value;
    if (!isCardInHand(rank, suit) && hand.length < 5) {
        hand.push({ rank, suit });
    } else {
        alert("This card has already been added to your hand.");
    }
    displayHand();
}
//Функция очистки руки игрока.
function clearHand() {
    if (hand.length != 0) {
        hand = [];
        displayHand();
        document.getElementById("task2Res").innerHTML = '';
    }
    else {
        document.getElementById("task2Res").textContent = "ERROR: Сначала нужно взять карту.";
    }
}
//Функция отображения карт руки игрока.
function displayHand() {
    const handList = document.getElementById('handList');
    handList.innerHTML = '';

    const maxCardsToShow = 5;

    // Используем метод slice для копирования массива
    hand.slice().forEach(currentCard => {
        const cardKey = `${currentCard.rank}_${currentCard.suit}`;
        const imgSrc = cardImages[cardKey];
        const listItem = document.createElement('div');
        const img = document.createElement('img');

        img.src = imgSrc;
        img.alt = `${currentCard.rank} ${currentCard.suit}`;
        img.title = `${currentCard.rank} ${currentCard.suit}`;

        listItem.appendChild(img);
        handList.appendChild(listItem);
    });
}
//Функция проверки наличия тройки в руке игрока.
function hasTriples() {
    const suitsCount = {};
    // Подсчитываем количество карт каждой масти в руке.
    for (const card of hand) {
        if (!suitsCount[card.suit]) {
            suitsCount[card.suit] = 1;
        } else {
            suitsCount[card.suit]++;
        }
    }
    // Проверяем, есть ли масть, которая встречается три раза.
    for (const suit in suitsCount) {
        if (suitsCount[suit] === 3) {
            return true;
        }
    }

    return false;
}
//Функция проверки наличия каре в руке игрока.
function hasQuads() {
    const suitsCount = {};
    // Подсчитываем количество карт каждой масти в руке.
    for (const card of hand) {
        if (!suitsCount[card.suit]) {
            suitsCount[card.suit] = 1;
        } else {
            suitsCount[card.suit]++;
        }
    }
    // Проверяем, есть ли масть, которая встречается четыре раза.
    for (const suit in suitsCount) {
        if (suitsCount[suit] === 4) {
            return true;
        }
    }

    return false;
}
//Функция вывода итогового сообщения.
function determineHandType() {
    try {
        if (hand.length == 5) {
            if (hasQuads()) {
                document.getElementById("task2Res").textContent = "Есть каре!";
                return;
            } else if (hasTriples()) {
                document.getElementById("task2Res").textContent = "Увы, у вас только тройка.";
                return;
            } else {
                throw new Error("Нет игры :C");
            }
        }
        else
            document.getElementById("task2Res").textContent = "ERROR: Пожалуйста закончите покерную раздачу!";
    }
    catch (error) {
        console.log(error);
    }
    finally {
    }
}