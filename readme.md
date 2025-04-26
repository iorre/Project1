
## Решение с использованием паттерна "Стратегия"

1. Создали **enum class ``DestructionType``** с типами "уничтожения аномалии".
2. Объявили **базовый класс ``DestructionStrategy``** и его **наследников ``TotalAnnihilationStategy`` ``HalfDestroyedStategy`` ``NoVictimsStategy``**.
3. В базовом классе ``DestructionStrategy`` создали метод ``Destruction()`` и переопределили его в каждом из наследников **
4. Создали фабричный метод ``CreateDestructionStrategy``
5. В базовом классе ``SpaceAnomaly`` добавили метод ``DestructionUsingStrategy()``, который проверяет тип стратегии
и, если она **не nullptr**, применяет к ней функцию ``Destruction()`` определенную в наследниках ``DestructionStrategy``.
6. В ``SpaceAnomaly`` создали метод ``Destruction()``, который вызывает ``DestructionUsingStrategy()``,
чтобы напрямую вызывать ``Destruction()`` у **всех** наследников ``SpaceAnomaly``.
7. В ``SpaceAnomaly`` добавили метод ``SetDestructionType()`` для передачи типа стратегии напрямую в базовый класс для дальнейшей работы.
8. В конструкторах наследников ``SpaceAnomaly`` предопределили тип стратерии при помощи конструкции
``SetDestructionType(CreateDestructionStrategy(DestructionType::X))`` (Вместо "X" тип стратегии).
9. Изменили функцию ``AnalyzeAll()`` на ``DestructionAll()``, соответственно поменяли
``currentAnomaly->Analyze()`` на ``currentAnomaly->Destruction()`` для вывода метода ``Destruction()``.
10. В деструктор ``~SpaceAnomaly()`` добавили очистку памяти

Решение с использованием паттерна "Шаблонный метод" было выполнено во время решения "Стратегии"



