
#-------------------------------------------------
#
# Project created by QtCreator 2015-07-26T16:38:25
#
#-------------------------------------------------

QT       += core gui
QT       += network sql xml
QT += printsupport
QT += serialport
QT += widgets \
    sql

VERSION = 1.4.0.1

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


TARGET = DigitalMeatProcessing
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dlgabout.cpp \
    dlgsettings.cpp \
    CommonObjects/aansprekingen.cpp \
    CommonObjects/afdelingen.cpp \
    CommonObjects/betalingstermijn.cpp \
    CommonObjects/bkhcategorie.cpp \
    CommonObjects/btwregimes.cpp \
    CommonObjects/commonobjects.cpp \
    CommonObjects/firma.cpp \
    CommonObjects/gebruikers.cpp \
    CommonObjects/geslachten.cpp \
    CommonObjects/kortingscategorie.cpp \
    CommonObjects/landen.cpp \
    CommonObjects/postcodes.cpp \
    CommonObjects/sites.cpp \
    CommonObjects/talen.cpp \
    Relaties/findrelaties.cpp \
    Relaties/relatiefiche.cpp \
    Relaties/relaties.cpp \
    Relaties/relatiesettings.cpp \
    ArtikelBeheer/artikelnummerbeheer.cpp \
    Relaties/btndeligate.cpp \
    ArtikelBeheer/addproduct.cpp \
    ArtikelBeheer/producten.cpp \
    my_lbfoto.cpp \
    ArtikelBeheer/addsoort.cpp \
    ArtikelBeheer/soorten.cpp \
    ArtikelBeheer/adddetail.cpp \
    ArtikelBeheer/details.cpp \
    ArtikelBeheer/specificaties.cpp \
    ArtikelBeheer/addspecificatie.cpp \
    ArtikelBeheer/comeenheden.cpp \
    ArtikelBeheer/addeenheid.cpp \
    CommonObjects/btwtarieven.cpp \
    CommonObjects/addbtwtarief.cpp \
    ArtikelBeheer/artikelen.cpp \
    ArtikelBeheer/allergenen.cpp \
    ArtikelBeheer/addallergenen.cpp \
    ArtikelBeheer/selectallergenen.cpp \
    ArtikelBeheer/addconcurentprijs.cpp \
    ArtikelBeheer/prijzenconcurentie.cpp \
    ArtikelBeheer/ingredienten.cpp \
    ArtikelBeheer/ingredient_artikel.cpp \
    ArtikelBeheer/addingredienten.cpp \
    Productie/lotnummers.cpp \
    Productie/lotnummerdata.cpp \
    ArtikelBeheer/berekenbtw.cpp \
    CommonObjects/stocklocaties.cpp \
    Productie/samengesteldelotnummers.cpp \
    Productie/lotnummerdbevat.cpp \
    Weegschaal/bedienscherm.cpp \
    CommonObjects/numkeyboard.cpp \
    Weegschaal/tickerow.cpp \
    CommonObjects/personeel.cpp \
    Weegschaal/ticket.cpp \
    Weegschaal/ticketline.cpp \
    Weegschaal/klantenscherm.cpp \
    Weegschaal/kassa.cpp \
    Boekhouding/kasboek.cpp \
    Productie/zoeklotopartikel.cpp \
    Rapportering/dagrapport.cpp \
    CommonObjects/printpagebackground.cpp \
    Bestellingen/bestelheader.cpp \
    Bestellingen/bestellijn.cpp \
    Facturatie/factuurfiche.cpp \
    Facturatie/factuurheader.cpp \
    Facturatie/factuurline.cpp \
    Facturatie/factuurregel.cpp \
    Facturatie/factuurkeuzelijst.cpp \
    Facturatie/factuurvanticket.cpp \
    Rapportering/betaalmiddel.cpp \
    ArtikelBeheer/prijscontrole.cpp \
    ArtikelBeheer/leveringenlijst.cpp \
    ArtikelBeheer/leveringenfiche.cpp \
    Bestellingen/leveringenheader.cpp \
    Bestellingen/leveringenline.cpp \
    ArtikelBeheer/leveringenregel.cpp \
    ArtikelBeheer/leveranciercodes.cpp \
    ArtikelBeheer/levcodefiche.cpp

HEADERS  += mainwindow.h \
    dlgabout.h \
    dlgsettings.h \
    CommonObjects/aansprekingen.h \
    CommonObjects/afdelingen.h \
    CommonObjects/betalingstermijn.h \
    CommonObjects/bkhcategorie.h \
    CommonObjects/btwregimes.h \
    CommonObjects/commonobjects.h \
    CommonObjects/commonobjects_global.h \
    CommonObjects/firma.h \
    CommonObjects/gebruikers.h \
    CommonObjects/geslachten.h \
    CommonObjects/kortingscategorie.h \
    CommonObjects/landen.h \
    CommonObjects/postcodes.h \
    CommonObjects/sites.h \
    CommonObjects/talen.h \
    Relaties/findrelaties.h \
    Relaties/relatiefiche.h \
    Relaties/relaties.h \
    Relaties/relatiesettings.h \
    ArtikelBeheer/artikelnummerbeheer.h \
    Relaties/btndeligate.h \
    ArtikelBeheer/addproduct.h \
    ArtikelBeheer/producten.h \
    my_lbfoto.h \
    ArtikelBeheer/addsoort.h \
    ArtikelBeheer/soorten.h \
    ArtikelBeheer/adddetail.h \
    ArtikelBeheer/details.h \
    ArtikelBeheer/specificaties.h \
    ArtikelBeheer/addspecificatie.h \
    ArtikelBeheer/comeenheden.h \
    ArtikelBeheer/addeenheid.h \
    CommonObjects/btwtarieven.h \
    CommonObjects/addbtwtarief.h \
    ArtikelBeheer/artikelen.h \
    ArtikelBeheer/allergenen.h \
    ArtikelBeheer/addallergenen.h \
    ArtikelBeheer/selectallergenen.h \
    ArtikelBeheer/addconcurentprijs.h \
    ArtikelBeheer/prijzenconcurentie.h \
    ArtikelBeheer/ingredienten.h \
    ArtikelBeheer/ingredient_artikel.h \
    ArtikelBeheer/addingredienten.h \
    Productie/lotnummers.h \
    Productie/lotnummerdata.h \
    ArtikelBeheer/berekenbtw.h \
    CommonObjects/stocklocaties.h \
    Productie/samengesteldelotnummers.h \
    Productie/lotnummerdbevat.h \
    Weegschaal/bedienscherm.h \
    Weegschaal/weegschaal.h \
    CommonObjects/numkeyboard.h \
    Weegschaal/tickerow.h \
    CommonObjects/personeel.h \
    Weegschaal/ticket.h \
    Weegschaal/ticketline.h \
    Weegschaal/klantenscherm.h \
    Weegschaal/kassa.h \
    Boekhouding/kasboek.h \
    Productie/zoeklotopartikel.h \
    Rapportering/dagrapport.h \
    CommonObjects/printpagebackground.h \
    Bestellingen/bestelheader.h \
    Bestellingen/bestellijn.h \
    Facturatie/factuurfiche.h \
    Facturatie/factuurheader.h \
    Facturatie/factuurline.h \
    Facturatie/factuurregel.h \
    Facturatie/factuurkeuzelijst.h \
    Facturatie/factuurvanticket.h \
    Rapportering/betaalmiddel.h \
    ArtikelBeheer/prijscontrole.h \
    ArtikelBeheer/leveringenlijst.h \
    ArtikelBeheer/leveringenfiche.h \
    Bestellingen/leveringenheader.h \
    Bestellingen/leveringenline.h \
    ArtikelBeheer/leveringenregel.h \
    ArtikelBeheer/leveranciercodes.h \
    ArtikelBeheer/levcodefiche.h

FORMS    += mainwindow.ui \
    dlgabout.ui \
    dlgsettings.ui \
    Relaties/findrelaties.ui \
    Relaties/relatiefiche.ui \
    Relaties/relatiesettings.ui \
    ArtikelBeheer/artikelnummerbeheer.ui \
    ArtikelBeheer/addproduct.ui \
    ArtikelBeheer/addsoort.ui \
    ArtikelBeheer/adddetail.ui \
    ArtikelBeheer/addspecificatie.ui \
    ArtikelBeheer/addeenheid.ui \
    CommonObjects/addbtwtarief.ui \
    ArtikelBeheer/addallergenen.ui \
    ArtikelBeheer/selectallergenen.ui \
    ArtikelBeheer/addconcurentprijs.ui \
    ArtikelBeheer/addingredienten.ui \
    Productie/lotnummers.ui \
    ArtikelBeheer/berekenbtw.ui \
    Productie/samengesteldelotnummers.ui \
    Weegschaal/bedienscherm.ui \
    CommonObjects/numkeyboard.ui \
    Weegschaal/tickerow.ui \
    Weegschaal/klantenscherm.ui \
    Weegschaal/kassa.ui \
    Productie/zoeklotopartikel.ui \
    Rapportering/dagrapport.ui \
    Facturatie/factuurfiche.ui \
    Facturatie/factuurregel.ui \
    Facturatie/factuurkeuzelijst.ui \
    Facturatie/factuurvanticket.ui \
    Rapportering/betaalmiddel.ui \
    ArtikelBeheer/prijscontrole.ui \
    ArtikelBeheer/leveringenlijst.ui \
    ArtikelBeheer/leveringenfiche.ui \
    ArtikelBeheer/leveringenregel.ui \
    ArtikelBeheer/levcodefiche.ui

RESOURCES += \
    resource.qrc

