Zakazane zadanie rekrutacyjne

System generowania osłon jest implementowane za pomocą trzech klas:

- Cover system controller: odpowiada za zarządzanie kolekcją miejsc do schowania się i kolekcją postaci szukających takich miejsc. System wspiera dynamiczne dodawanie/usuwanie elementów systemu w czasie gameplayu.
- CoverPlace: Aktor będący fizyczną reprezentacją miejsca do schowania się. Pozwala zdefiniować dla siebie kierunki w których postać może strzelać oraz z których jest osłaniana. Generuje informacje na temat wrogów mogących oddziałwywać w jakiś sposób na postać zajmującą to miejsce.
- CoverSystemActorComponent: actor component, który po dodaniu do dowolnego aktora będzie znajdywał dla niego optymalne miejsce do schowania się

Wybieranie odpowiedniej osłony odbywa się na podstawie liczenia "punktacji ważonej" dla każdego z miejsc, gdzie punktowane dodatnio lub ujemnie są różne aspekty dotyczące danego punktu, a wagi mogą być ustawione indywidualnie dla każdego rodzaju postaci.

Dodawanie nowego miejsca odbywa się poprzez wrzucenia blueprinta BP_coverPlace na scene(na scenie muis się również znajdować BP_CoverSystemController) i konfiguracja jego właściwości.

Zadanie zostało rozszerzone o prosty system AI postaci, ktory wykorzystuje system osłon oraz system strzelania śmierci i respawnu. Po włączeniu gry, powinny pojawić się dwa przyciski służące do respawnowania postaci w dwóch drużynach.
  
