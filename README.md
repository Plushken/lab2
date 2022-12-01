# lab2
Данное приложение разработано для получение основной информации изображения из графического файла, файлов,архива файлов. Полученная изформация состоит из:
* имя файла

* расширение изображения

* размер изображения в битах

* размер изображения в пикселях

* глубину цвета изображения

* разрешение изображения (dpi)
-
В данном приложении мы обрабатывем файлы с расширение: jpg, gif, tif, bmp, png, pcx, jpeg; а также архивы с расширением .zip.
___
Приложение разработано с помощью кроссплатформенной IDE — Qt Creator (версия: 4.11.1). Адаптировано для ОС Windows.

Приложение использует класс `QZipReader` и стандартные библиотеки Qt: `QtWidgets`. Документация по данной среде разработки и ее библиотекам доступна на ее [веб-сайте](https://doc.qt.io).
___
Функционал приложения представляет из себя считывание информации об изображениях и ее представление в виде таблицы.

Базовый класс приложения — `Widget`. Его функционал: 

* выбор файла/файлов/архива файлов при помощи класса `QFileDialog`

* создание временной директории и распаковка архива в нее при помощи классов `QDir` и `QZipReader`

* вывод предупреждения при отсутствии файлов нужного формата в архиве при помощи класса `QMessageBox`

* считывание данных файла при помощи классов `QFileInfo` и `QImage`

* представление и возможность сортировки данных при помощи классов `QTableWidget` и `QTableWidgetItem`
