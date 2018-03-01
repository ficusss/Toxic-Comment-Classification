# Toxic Comment Classification (TCC)

![Баннер](https://github.com/ficusss/Toxic-Comment-Classification/blob/master/banner0.png)

## Введение. Цель проекта

Количество комментариев, ежедневно оставляемых пользователями в сети, огромно, и многие из них являются в той или иной степени оскорбительными. Очевидно, что в деле своевременного выявления и классификации таких сообщений сейчас не обойтись без автоматизации, поскольку она позволяет анализировать огромное количество данных за короткое время. 
Предлагаемый нами продукт поможет владельцам различных социальных платформ значительно упростить процесс проверки подозрительных пользовательских сообщений на предмет соответствия политике компании. Он хорошо подстраивается под правила конкретного сервиса, так как позволяет классифицировать, какого рода "недоброжелательность" высказана в том или ином сообщении, а также определить процентное соотношение этих видов "недоброжелательности" в исследуемом комментарии.

### Все виды "недоброжелательности", поддерживаемые на данный момент:
  * оскорбительный;
  * чрезвычайно оскорбительный;
  * непристойный;
  * угрожающий;
  * унизительный;

## Сравнение с аналогами

| Название продукта | Интерактивная обработка | Классификация содержания | Поддержка русского языка | GUI | Открытый исходный код | 
|-------------------|:---:|:---:|:---:|:---:|:---:|
|[**TCC**](https://github.com/grisha-feoktistov/Toxic-Comment-Classification) | **-** | **+** | **+** | **+** | **+** |
|[Perspective](http://www.perspectiveapi.com/#/) | **+** | **-** | **-** | **+** | **-** | 
|[Detecting insults](https://github.com/tuzzeg/detect_insults)| **-** | **-** | **-** | **-** | **+** |





Для простого выявления агрессивных сообщений есть большое число средств, однако, представленная работа позволяет получить более детальную информацию, полезную не только при поддержании порядка, но и при анализе аудитории ресурса.


## Требования к аппаратуре


## Требования к программному обеспечению


## Средства разработки программного продукта


## Характеристики продукта


## Формат входных данных

Поддерживаются два возможных формата входных данных:
  * Файл с текстом в кодировке Unicode без дополнительного оформления на английском языке. Поддерживаемые форматы файлов:
    - .txt
  * Текст в кодировке Unicode без дополнительного оформления на английском языке, введенный в специальное текстовое поле в рабочем окне программы.

Специальные возможности:
  * Возможно указать желаемый разделитель текстов в файле/текстовом поле, если они должны анализироваться незаисимо друг от друга.
  * Возможно указать желаемый идентификатор для текста выделив его парным тегом **<title> ... </title>** перед самим текстом. По умолчанию тексты идентифицируются согласно своему порядковому номеру, начиная с 1.
  
Размер входных данных никак не ограничен явно. Но он ограничен объемами оперативной памяти используемого ЭВМ.

## Формат выходных данных

Вывод данных возможен в ледующих форматах: 
  * В файл в формате *.txt*.
  * В специальное поле в окне экрана.

Формат выходных данных:
  >Текст - Идентификатор текста.  
     - категория 1 - вероятность, с которой текст к ней относится  
     - категория 2 - вероятность, с которой текст к ней относится  
       ...  
     - категория n - вероятность, с которой текст к ней относится  
     
Специальные возможности:
  * Возможно включить вывод самого текста в результирующие данные. Тогда формат данных будет следующим:
  >Текст - Идентификатор текста.  
   Содержание - (сам текст).  
     категория 1 - вероятность, с которой текст к ней относится  
     категория 2 - вероятность, с которой текст к ней относится  
      ...  
     категория n - вероятность, с которой текст к ней относится  

## Установка продукта


## Запуск продукта


## Описание интерфейса пользователя


## Описание API библиотеки


## Детали реализации


## Тестирование


## Ссылки и литература
* Tajinder Singh, Madhu Kumar, ["Role of Text Pre-Processing in Twitter Sentiment Analysis"](https://www.sciencedirect.com/science/article/pii/S1877050916311607), 2016
* Richard Socher, Alex Perelygin, Jean Y. Wu, Jason Chuang, Christopher D. Manning, Andrew Y. Ng and Christopher Potts, ["Recursive Deep Models for Semantic Compositionality Over a Sentiment Treebank"](https://nlp.stanford.edu/~socherr/EMNLP2013_RNTN.pdf), 2013
* Серия статей "Another Twitter sentiment analysis" [(часть 1)](https://towardsdatascience.com/another-twitter-sentiment-analysis-bb5b01ebad90)

