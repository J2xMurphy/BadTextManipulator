#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(int argc_in, char * argv_in[],QWidget *parent)
    : QMainWindow(parent)
    , argc(argc_in)
    , argv(argv_in)
    , ui(new Ui::MainWindow)
{
    setWindowTitle(WINDOW_TITLE);
    opened_file = "";
    search_term = "";
    replace_term = "";
    search_direction = next_;
    search_operation = find_;
    ui->setupUi(this);

    s_bar = this->findChild<QStatusBar *>("statusbar");
    setupStatusBar(s_bar);

    t_box = findChild<QTextBrowser *>("textBox");
    setupShortcuts();

    var_box = NULL;
    value_box = NULL;

    QObject::connect(this,SIGNAL(varlist_edited()),
                     this,SLOT(refresh_vblist()));

    args_handler();
    std::cout  << "Ending initialization" << std::endl;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::args_handler()
{
    std::cout << argc << std::endl;
    std::cout << argv[0] << std::endl;
    if (argc==2){
        open_file(argv[1]);
    }
}

void MainWindow::addvar(QString key, QString pair)
{
    varlist.insert(key,pair);
}

//TODO
void MainWindow::setupShortcuts()
{
    QShortcut * short_find = new QShortcut(QKeySequence(tr("Ctrl+F", "Edit|Find...")),this);
    QObject::connect(short_find,SIGNAL(activated()),this,SLOT(on_actionFind_triggered()));

    QShortcut * short_open = new QShortcut(QKeySequence(tr("Ctrl+O", "File|Open...")),this);
    QObject::connect(short_open,SIGNAL(activated()),this,SLOT(on_actionOpen_triggered()));

    QShortcut * short_replace = new QShortcut(QKeySequence(tr("Ctrl+R", "Edit|Find...")),this);
    QObject::connect(short_replace,SIGNAL(activated()),this,SLOT(on_actionReplace_triggered()));

    QShortcut * short_new = new QShortcut(QKeySequence(tr("Ctrl+N", "File|New...")),this);
    QObject::connect(short_new,SIGNAL(activated()),this,SLOT(on_actionNew_triggered()));

    QShortcut * short_undo = new QShortcut(QKeySequence(tr("Ctrl+Z", "Edit|Undo")),this);
    QObject::connect(short_undo,SIGNAL(activated()),this,SLOT(on_actionUndo_triggered()));

    QShortcut * short_redo = new QShortcut(QKeySequence(tr("Ctrl+Y", "Edit|Redo")),this);
    QObject::connect(short_redo,SIGNAL(activated()),this,SLOT(on_actionRedo_triggered()));

//    DISABLED DURING TESTING
//    QShortcut * short_save = new QShortcut(QKeySequence(tr("Ctrl+S", "Edit|Find...")),this);
//    QObject::connect(short_save,SIGNAL(activated()),this,SLOT(on_actionFind_triggered()));
}

void MainWindow::setupStatusBar(QStatusBar * stabar)
{
    stabar->showMessage("0");
    QLabel * s_info = new QLabel(NULL_SEARCH_TERM);
    s_info->setObjectName("s_info");

    QPushButton * search_left = new QPushButton, * search_right = new QPushButton;
    search_left->setText("<");
    search_right->setText(">");

    search_left->setMaximumWidth(20);
    search_right->setMaximumWidth(20);

    QObject::connect(search_right,SIGNAL(pressed()),this,SLOT(search_next()));
    QObject::connect(search_left,SIGNAL(pressed()),this,SLOT(search_prev()));

    stabar->addPermanentWidget(search_left);
    stabar->addPermanentWidget(s_info);
    stabar->addPermanentWidget(search_right);
}

void MainWindow::on_actionOpen_triggered()
{
    //OPENS A FILE DIALOG
    QString dir;
    dir = QFileDialog::getOpenFileName(this,
        "Open...", "", "Filetypes (*.txt)");
    open_file(dir);
}

void MainWindow::open_file(QString dir)
{
    //OPENS FILE FROM DIALOG, RETURNS IF ERROR
    // FUNCTION SHOULD HAVE RELAVANT RETURN STATEMENT
    QFile file(dir);
    if (file.open(QIODevice::ReadOnly)!=1){
        std::cout << dir.toStdString() << " could not be opened." << std::endl;
        return;
    }

    //READS DATA FROM OPENED FILE, THEN CLOSES
    opened_file = dir;
    QDataStream f_in(&file);
    char n[file.size()];
    f_in.readRawData(n,file.size());
    file.close();

    //TITLE BECOMES FILE LOCATION, WORD COUNT UPDATED, AND TEXT APPLIED
    setWindowTitle(dir);
    t_box->clear();
    t_box->setPlainText(n);
    update_word_count();
}

void MainWindow::on_actionSave_triggered()
{
    //STOPS IF NO FILE OPENED
    if (opened_file=="")return;

    //OPENS FILE FROM LAST ACCESSED LOCATION, RETURN IF CANNOT
    QFile file(opened_file);
    if (file.open(QIODevice::WriteOnly)!=1){
        std::cout << SAVE_ERROR << std::endl;
        return;
    }

    //WRITES TO FILE, THEN CLOSES
    QByteArray text = t_box->toPlainText().toLocal8Bit();
    file.write(text);
    file.close();
}


void MainWindow::on_actionSave_As_triggered()
{
    //OPENS A FILE DIALOG TO SELECT OPENED FILE, THEN DOES NORMAL SAVE
    opened_file = QFileDialog::getSaveFileName(this,"Save as...","","*.txt");
    on_actionSave_triggered();

}


void ::MainWindow::update_word_count()
{
    //SENDS WORD COUNT TO STATUS BAR
    s_bar->showMessage(
        QString::number(findChild<QTextBrowser *>("textBox")->toPlainText().length())
                );
}


void MainWindow::on_textBox_textChanged()
{
    // SLOT FOR WHEN TEXT IS EDITED
    update_word_count();
}


void MainWindow::on_actionFont_List_triggered()
{
    //INITIATES EMPTY DIALOG BOX
    QDialog font_select(this);
    QFormLayout f_layout(&font_select);

    //CREATES A SCROLLING LIST OF FONTS FOR THE DIALOG BOX
    QFontComboBox * font_scroll = new QFontComboBox;
    font_scroll->setCurrentFont(t_box->currentFont());
    f_layout.addRow(new QLabel(FONT_TYPE_PROMPT),font_scroll);

    //CREATES AN INT LIST FOR DIALOG BOX
    QSpinBox * font_spin = new QSpinBox;
    font_spin->setRange(4,50);
    font_spin->setValue(t_box->font().pointSize());
    f_layout.addRow(new QLabel(FONT_TYPE_PROMPT),font_spin);

    //BUTTON TO END DIALOG BOX
    QPushButton * accept= new QPushButton("Apply");
    f_layout.addRow(accept);
    QObject::connect(accept,SIGNAL(clicked()),&font_select,SLOT(accept()));

    //DISPLAYS DIALOG BOX
    font_select.exec();

    //SETS TEXT BOX'S FONT TO DIALOG BOX'S RESULTS
    QFont q;
    q.setFamily(font_scroll->currentFont().toString());
    q.setPointSize(font_spin->value());
    t_box->setFont(q);

    //CLEANUP
    delete font_scroll;
    delete font_spin;
    delete accept;
}

void MainWindow::on_actionSelector_triggered()
{
    //CREATES A DIALOG AND SHOWS SELECTED TEXT IN A BOX,
    //WAS FOR TESTING LIKELY NOW DEPRICATED
    QDialog show_results(this);
    QFormLayout f_layout(&show_results);
    f_layout.addWidget(new QLabel(get_Selected_Text()));

    show_results.exec();
}

QString MainWindow::get_Selected_Text()
{
    //RETURNS TEXT SELECTED IN TEXT BOX
    return t_box->textCursor().selectedText();
}

void MainWindow::on_actionFind_triggered()
{
    //CREATE INPUT DIALOG FOR A STRING, AND SETS SEARCH DIRECTION TO RIGHT
    QInputDialog * QI = new QInputDialog;
    QString lol = QI->getText(this,"Find...","Find text:",QLineEdit::Normal,search_term);
    search_direction = next_;

    //SAVES SEARCH TERN AND SHOWS IT IN STATUS BAR
    search_term = lol;
    s_bar->findChild<QLabel*>("s_info")->setText(lol);

    //EXECUTES SEARCH
    word_Search(lol);
    search_operation = find_;

    //CLEANUP
    delete QI;
}

bool MainWindow::word_Search(QString word, bool direction)
{
    //INIT VARIABLES
    QString text;
    int found_index;

    //SEARCHES LEFT OR RIGHT DEPENDING ON ARG2
    text = t_box->toPlainText();
    if (direction == true){
        std::cout << "Looking forward ";
        found_index = text.indexOf(word,t_box->textCursor().position());
        std::cout << found_index << " ";
    }
    if (direction == false){
        std::cout << "Looking back ";
        found_index = text.lastIndexOf(word,t_box->textCursor().position()-word.length()-1);
        std::cout << found_index << " ";
    }

    std::cout << direction << std::endl;

    //HIGHLIGHTS TEXT BASED ON WHERE IT WAS FOUND AND GIVEN WORD LENGTH, ERRORS OTHERWISE
    if (found_index == -1){
        if (direction == 1)
            push_message_box("'"+word+"' not found after cursor.","Find...");
        if (direction == 0)
            push_message_box("'"+word+"' not found before cursor.","Find...");
        return false;
    }else{
        QTextCursor QTC = t_box->textCursor();
        QTC.setPosition(found_index);
        QTC.setPosition(found_index+(word.length()), QTextCursor::KeepAnchor);
        t_box->setTextCursor(QTC);
        return true;
    }

}

void MainWindow::push_message_box(QString message,QString title)
{
    //CREATES A MESSAGE BOX WITH GIVEN MESSAGE AND TITLE
    QMessageBox * QMB = new QMessageBox;
    QMB->setWindowTitle(title);
    QMB->setText(message);
    QMB->exec();

    //CLEANUP
    delete QMB;
}

void MainWindow::on_actionNew_triggered()
{
    //CLEARS THE CURRENT FILE, RESETS OPENED FILE AND TITLE.
    t_box->clear();
    opened_file = "";
    setWindowTitle(WINDOW_TITLE);
}


void MainWindow::on_actionFrom_Url_triggered()
{
    // CREATES AN INPUT DIALOG FOR A WEBSITE
    QInputDialog * QI = new QInputDialog;
    QString url = QI->getText(this,"From Url...","Webtext:",QLineEdit::Normal,"");

    //RUN THE DOWNLOADER AND SET TEXT
    QString content = downloader(url);
    t_box->setPlainText(content);

    //CLEANUP
    delete QI;
}

QString MainWindow::downloader(QString Url)
{
    // CREATES A WAITING DOWNLOADER WITH URL
    QNetworkAccessManager manager;
    QNetworkReply *response = manager.get(QNetworkRequest(QUrl(Url)));

    //LOOP/LOCK TO WAIT FOR RESULTS FROM DOWNLOADER
    QEventLoop wait;
    connect(response, SIGNAL(finished()), &wait, SLOT(quit()));
    wait.exec();

    //GETS TEXT FROM PULLED DATA, AND SETS IT TO TEXT BOX
    QString content = response->readAll();

    //CLEANUP
    manager.deleteLater();
    return content;
}

void MainWindow::on_actionReplace_triggered()
{
    //CREATES INPUT DIALOG FOR REPLACE FUNCTION
    QDialog replace_select(this);
    QFormLayout r_layout(&replace_select);

    //CREATES FIND INPUT FOR REPLACE FUNCTION
    QLineEdit * find = new QLineEdit;
    r_layout.addRow(new QLabel(FIND_PROMPT),find);

    //CREATES WORD TO REPLACE INPUT FOR REPLACE FUNCTION
    QLineEdit * replace = new QLineEdit;
    r_layout.addRow(new QLabel(REPLACE_PROMPT),replace);

    //CREATES ENDING BUTTON FOR REPLACE FUNCTION
    QPushButton * accept= new QPushButton("Accept");
    r_layout.addRow(accept);
    QObject::connect(accept,SIGNAL(clicked()),&replace_select,SLOT(accept()));

    //SHOWS INPUT DIALOG, AND REPLACES WITH GIVEN INPUTS
    replace_select.exec();
    search_term = find->text();
    replace_term = replace->text();
    search_operation = repl_;
    search_direction = next_;
    do_replace(find->text(),replace->text());
    s_bar->findChild<QLabel*>("s_info")->setText(find->text()+":"+replace->text());

    //CLEANUP
    delete find;
    delete replace;
    delete accept;

}

bool MainWindow::do_replace(QString find, QString replace,bool direction)
{
    //WORD SEARCH HIGHLIGHTS THE WORD, THEN CLEARS THE HIGHLIGHED WORDS,
    //INSERTS REPLACE TEXT, HIGHLIGHTS NEW TEXT
    if (word_Search(find,direction)){
        int pos = t_box->textCursor().position();
        t_box->clearFocus();
        t_box->insertPlainText(replace);

        //SETS REPLACE CURSOR TO BEGINNING OF REMOVED WORD, THEN TO END OF NEW WORD
        QTextCursor QTC = t_box->textCursor();
        QTC.setPosition(pos-find.length());
        QTC.setPosition(pos-find.length()+replace.length(),QTextCursor::KeepAnchor);
        t_box->setTextCursor(QTC);

        return 1;
    }else{
        //INCASE OF ERROR
        return 0;
    }
}

void MainWindow::set_search_term(QString term)
{
    //UNUSED
    //SAVES SEARCH TERM AND SENDS IT TO STATUS BAR
    search_term = term;
    s_bar->findChild<QLabel*>("s_info")->setText(term);
}

void list_children(QWidget * parent)
{
    //DEBUG FOR GETTING LIST OF CHILDREN
    QList <QWidget*> asd;
    asd = parent->findChildren<QWidget*>();
    for (QWidget * d : asd){
        std::cout << d->objectName().toStdString() << std::endl;
    }
}

void MainWindow::search_next()
{
    //BASED ON SAVED INFORMATION, DOES A NORMAL SEARCH
    if (search_operation == find_){
        word_Search(search_term);
    }
    if (search_operation == repl_){
        do_replace(search_term,replace_term);
    }
}

void MainWindow::search_prev()
{
    //BASED ON SAVED INFORMATION, DOES A REVERSE SEARCH
    if (search_operation == find_){
        word_Search(search_term,0);
    }
    if (search_operation == repl_){
        do_replace(search_term,replace_term,0);
    }
}

void MainWindow::on_actionUndo_triggered()
{
    //WHEN THE HOTKEY OR ACTION IS USED, UNDOES
    std::cout << "Undo triggered" << std::endl;
    t_box->undo();

}


void MainWindow::on_actionRedo_triggered()
{
    //WHEN THE HOTKEY OR ACTION IS USED, REDOES
    std::cout << "Redo triggered" << std::endl;
    t_box->redo();
}


void MainWindow::on_actionView_Help_triggered()
{
    //THROWS THE HELP TEXT INTO A BASIC MESSAGE BOX
    push_message_box(HELP_TEXT,"Help");
}


void MainWindow::on_actionAbout_triggered()
{
    //THROWS THE ABOUT TEXT INTO A BASIC MESSAGE BOX
    push_message_box(ABOUT_TEXT,"About");
}


void MainWindow::on_actionAdd_Variable_triggered()
{
    //CREATES INPUT DIALOG FOR ADD VARIABLE FUNCTION
    QDialog addvar_dialog(this);
    QFormLayout v_layout(&addvar_dialog);

    //CREATES INPUT FOR VARIABLE KEY FUNCTION
    QLineEdit * addvar_key = new QLineEdit;
    v_layout.addRow(new QLabel(ADDVARKEY_PROMPT),addvar_key);

    //CREATES INPUT FOR VARIABLE PAIR FUNCTION
    QLineEdit * addvar_pair = new QLineEdit;
    v_layout.addRow(new QLabel(ADDVARPAIR_PROMPT),addvar_pair);

    //CREATES ENDING BUTTON FOR ADD VARIABLE FUNCTION
    QPushButton * accept= new QPushButton("Accept");
    v_layout.addRow(accept);
    QObject::connect(accept,SIGNAL(clicked()),&addvar_dialog,SLOT(accept()));

    addvar_dialog.exec();
    if (addvar_key->text() != "")
    addvar(addvar_key->text(),addvar_pair->text());

    //CLEANUP
    delete accept;
    delete addvar_key;
    delete addvar_pair;
    emit varlist_edited();
}


void MainWindow::on_actionVariables_triggered()
{
    //CREATE INPUT DIALOG FOR THE LIST VARIABLE FUNCTION
    QDialog addvar_dialog(this);
    QHBoxLayout h_layout(&addvar_dialog);

    //ADDS THE GLOBAL VARLIST WIDGET TO THE DIALOG BOX
    var_box = new QListWidget;
    refresh_vblist();
    h_layout.addWidget(var_box);

    //THE CENTER BOX WITH FUCTIONS TO ADD AND REMOVE VARIABLE BUTTONS
    QWidget buttontower;
    QPushButton * addvar = new QPushButton(VARLISTADD_PROMPT);
    QPushButton * editvar = new QPushButton (VARLISTEDIT_PROMPT);
    QPushButton * delvar = new QPushButton(VARLISTDEL_PROMPT);
    QVBoxLayout v_layout(&buttontower);
    v_layout.addWidget(addvar);
    v_layout.addWidget(editvar);
    v_layout.addWidget(delvar);
    h_layout.addWidget(&buttontower);

    //THE RIGHTMOST BOX WITH THE VALUES ASSOCIATED VARIABLES
    value_box = new QTextEdit;
    h_layout.addWidget(value_box);

    //CONNECT THE BOXES
    QObject::connect(addvar,SIGNAL(clicked()),
                     this,SLOT(on_actionAdd_Variable_triggered()));
    QObject::connect(editvar,SIGNAL(clicked()),
                     this,SLOT(reset_key()));
    QObject::connect(delvar,SIGNAL(clicked()),
                     this,SLOT(remove_key()));
    QObject::connect(var_box,SIGNAL(itemClicked(QListWidgetItem*)),
                     this,SLOT(populate_valuebox(QListWidgetItem*)));

    // ON CLICK
    addvar_dialog.exec();
    //CLEANUP
    delete addvar;
    delete delvar;
    delete var_box;
    var_box = NULL;
    delete value_box;
    value_box = NULL;
}


void MainWindow::on_actionExport_triggered()
{
    // Choose a tag system ya bum!
    QDialog export_dialog(this);
    export_dialog.setWindowTitle(EXPORT_TITLE);
    QVBoxLayout v_layout(&export_dialog);

    //ADDS THE PREVIEW TEXT BOX TO THE SCREEN
    QTextBrowser * preview_text = new QTextBrowser();
    preview_text->setReadOnly(true);
    v_layout.addWidget(preview_text);

    //ADDS THE FINALIZE EXPORT AND CANCEL BUTTONS TO THE SCREEN
    QWidget action_buttons;
    QHBoxLayout buttons_layout(&action_buttons);
    QPushButton * cancel_button = new QPushButton(CANCEL_DIALOG);
    QPushButton * export_button = new QPushButton(EXPORT_DIALOG);
    buttons_layout.addWidget(cancel_button);
    buttons_layout.addWidget(export_button);
    v_layout.addWidget(&action_buttons);

    QObject::connect(cancel_button,SIGNAL(clicked()),
                     &export_dialog,SLOT(reject()));
    QObject::connect(export_button,SIGNAL(clicked()),
                     this,SLOT(export_save()));
    QObject::connect(this,SIGNAL(export_finished(int)),
                     &export_dialog,SLOT(done(int)));

    //SETS THE TEXT IN THE PREVIEW BOX
    var_edited_text();
    preview_text->setText(*export_text);

    //EXECUTES
    export_dialog.exec();

    //CLEANUP
    delete preview_text;
    delete cancel_button;
    delete export_button;
}

void MainWindow::refresh_vblist()
{
    if (var_box == NULL)// var_box is null during normal add variable
        return;

    //clears and repopulates the list
    var_box->clear();
    var_box->addItems(varlist.keys());
}

void MainWindow::populate_valuebox(QListWidgetItem * var)
{
    assert(value_box != NULL);//THIS SHOULD ONLY BE CALLED WHEN value_box IS ALIVE
    //finds the variable in hashmap and sets it to the text
    value_box->setText(varlist.value(var->text()));
}

void MainWindow::reset_key()
{
    assert(value_box != NULL);//THIS SHOULD ONLY BE CALLED WHEN value_box IS ALIVE
    assert(var_box != NULL);//THIS SHOULD ONLY BE CALLED WHEN var_box IS ALIVE
    //
    addvar(var_box->currentItem()->text(),value_box->toPlainText());
}

void MainWindow::remove_key()
{
    assert(value_box != NULL);//THIS SHOULD ONLY BE CALLED WHEN value_box IS ALIVE
    assert(var_box != NULL);//THIS SHOULD ONLY BE CALLED WHEN var_box IS ALIVE
    //removes currently selected item from the stored list
    varlist.remove(var_box->currentItem()->text());
    refresh_vblist();
    value_box->setText("");
}

void MainWindow::var_edited_text()
{
    //Copies text from text box and replaces all vars with values
    export_text = new QString(t_box->toPlainText());
    for (QString key : varlist.keys()){
        export_text->replace(QString(BEGIN_TAG+key+END_TAG),varlist.value(key));
    }
}

void MainWindow::export_save()
{
    //Makes a file selector and opens selected file
    QString export_file = QFileDialog::getSaveFileName(this,EXPORT_DIALOG,"","*.txt");
    QFile file(export_file);
    if (file.open(QIODevice::WriteOnly)!=1){
        std::cout << SAVE_ERROR << std::endl;
        return;
    }

    //WRITES TO FILE, THEN CLOSES AND SIGNALS UPON COMPLETION
    QByteArray text = export_text->toLocal8Bit();
    file.write(text);
    file.close();
    emit export_finished(1);
}

// REDO
// Should really retry doing this, once the JSON formatting is figured out
void MainWindow::on_actionDefine_Selction_triggered()
{
    QString saved_word = get_Selected_Text();
    QString word = "https://api.dictionaryapi.dev/api/v2/entries/en/"+
                   saved_word;
//    QString word = "file:///D:/Users/Joseph/Desktop/Figure%20it%20out.json";

    qWarning() << word;
    QString content = downloader(word);
    QStringList meanings, definitions, synonyms, antonyms, examples;

    int found_index;
    found_index = content.indexOf("\"meanings\":",0);
    found_index = content.indexOf("\"definitions\":[",found_index);
    bool cont = true;

    //Each definition block begins and ends with "{" and "}" respectively
    //Use those to search and synonyms, antonyms, and examples can be added
    while(cont){
        int found_index1 = content.indexOf("{\"definition\":",found_index)+14;
        int found_index2 = content.indexOf("}",found_index1)+1;
        found_index = found_index2;
//        std::cout << found_index1 << ":" << found_index2 << std::endl;
        if (found_index1<=13){
            cont = false;
        }
        else{
            meanings.append(content.sliced(found_index1,found_index2-found_index1));
        }
    }
    qWarning() << "Getting to output";

    if (meanings.isEmpty()){
        push_message_box("No selection found.");
        return;
    }
    //Search for parts of every meanings
    for (QString strip: meanings){
//        qWarning() << strip;

        //Start with definitions
        int found_index1 = 1;
        int found_index2 = strip.indexOf("\",",found_index1);
//        qWarning() << found_index1 << ":" << found_index2;
        if (found_index1 != -1)
        definitions.append(strip.sliced(found_index1,found_index2-found_index1));

        //Move on to synonyms
        found_index1 = strip.indexOf("\"synonyms\":[",found_index2)+12;
        found_index2 = strip.indexOf("]",found_index1);
//        qWarning() << found_index1 << ":" << found_index2;
        if (found_index1 != -1)
        synonyms.append(strip.sliced(found_index1,found_index2-found_index1));

        //Move on to antonyms
        found_index1 = strip.indexOf("\"antonyms\":[",found_index2)+12;
        found_index2 = strip.indexOf("]",found_index1);
//        qWarning() << found_index1 << ":" << found_index2;
        if (found_index1 != -1)
        antonyms.append(strip.sliced(found_index1,found_index2-found_index1));

        //Move on to examples
        found_index1 = strip.indexOf("\"example\":",found_index2);
        found_index2 = strip.indexOf("\"",found_index1);
//        qWarning() << found_index1 << ":" << found_index2;
        if (found_index1 != -1){
            examples.append(strip.sliced(found_index1,found_index2-found_index1));}
        else{
            examples.append("");}
    }
    //push_message_box(meanings[0]);

    QDialog definition_dialog(this);
    definition_dialog.setWindowTitle(DEFINE_TITLE+saved_word);
    QHBoxLayout h_layout(&definition_dialog);

//DEFINE THE BUTTONS USED ON THE RIGHT OF DEFINITIONS
    QWidget UD_buttons;
    QVBoxLayout v_layout(&UD_buttons);
    dict_button * up = new dict_button(UP_ARROW,0);
    dict_button * down = new dict_button(DOWN_ARROW,1);
    up->resize(40,40);
    up->setMaximumSize(40,40);
    up->setLayoutDirection(Qt::RightToLeft);
    down->resize(40,40);
    down->setMaximumSize(40,40);
    down->setLayoutDirection(Qt::RightToLeft);

//ADD A QLABEL TO SHOW PAGE NUMBER
    QLabel * page = new QLabel();
    page->setObjectName("page_tex");
    page->setText("1/"+QString::number(meanings.length())+"    ");
    page->setLayoutDirection(Qt::RightToLeft);
    page->setAlignment(Qt::AlignRight|Qt::AlignVCenter);

//ADD TO RIGHTMOST LAYOUT IN ORDER
    v_layout.addWidget(up);
    v_layout.addWidget(page);
    v_layout.addWidget(down);

    QWidget words;
    QVBoxLayout text_layout(&words);

    QLabel * d = new QLabel(DEFINITION_LABEL);
    text_layout.addWidget(d);
    QLabel * dtext = new QLabel(
                (definitions[0].length()>0) ? definitions[0] : NO_DEFINITION);
    text_layout.addWidget(dtext);
    dtext->setObjectName("def_tex");

    QLabel * s = new QLabel(SYNONYM_LABEL);
    text_layout.addWidget(s);
    QLabel * stext = new QLabel(
                (synonyms[0].length()>0) ? synonyms[0] : NO_SYNONYM);
    stext->setObjectName("syn_tex");
    text_layout.addWidget(stext);

    QLabel * a = new QLabel(ANTONYM_LABEL);
    text_layout.addWidget(a);
    QLabel * atext = new QLabel(
                (antonyms[0].length()>0) ? antonyms[0] : NO_ANTONYM);
    atext->setObjectName("ant_tex");
    text_layout.addWidget(atext);

    QLabel * e = new QLabel(EXAMPLE_LABEL);
    text_layout.addWidget(e);
    QLabel * etext = new QLabel(
                (examples[0].length()>0) ? examples[0] : NO_EXAMPLE);
    etext->setObjectName("exa_tex");
    text_layout.addWidget(etext);

    dictionary f(0,definitions,synonyms,antonyms,examples,&definition_dialog);

    QObject::connect(up,SIGNAL(dclicked(bool)),
                     &f,SLOT(refresh(bool)));
    QObject::connect(down,SIGNAL(dclicked(bool)),
                     &f,SLOT(refresh(bool)));

    h_layout.addWidget(&words);
    h_layout.addWidget(&UD_buttons);

    definition_dialog.exec();
    //CLEANUP
    delete up;
    delete down;
    delete page;
    delete d;
    delete dtext;
    delete s;
    delete stext;
    delete a;
    delete atext;
    delete e;
    delete etext;
}

dictionary::dictionary(int p,QStringList d,QStringList s,QStringList a,
                       QStringList e,QWidget* w)
{
    page = p;
    definitions = d;
    synonyms = s;
    antonyms = a;
    examples = e;
    labels = w;
};

void dictionary::refresh(bool direction)
{
    page += (direction*2)-1;
    if (page < 0) page = definitions.length()-1;
    if (page > definitions.length()-1)page=0;
    qWarning() << "OOF" << page;
    labels->findChild<QLabel*>("def_tex")->setText((definitions[page].length()>0)
            ? definitions[page] : NO_DEFINITION);
    labels->findChild<QLabel*>("syn_tex")->setText((synonyms[page].length()>0)
            ? synonyms[page] : NO_SYNONYM);
    labels->findChild<QLabel*>("ant_tex")->setText((antonyms[page].length()>0)
            ? antonyms[page] : NO_ANTONYM);
    labels->findChild<QLabel*>("exa_tex")->setText((examples[page].length()>0)
            ? examples[page] : NO_EXAMPLE);
    list_children(labels);
    labels->findChild<QLabel*>("page_tex")->setText(QString::number(page)+
            "/"+QString::number(definitions.length())+"    ");
}

dict_button::dict_button(QString s,int n)
{
    setText(s);
    next = n;
    QObject::connect(this,SIGNAL(clicked()),
                     this,SLOT(ping_dict()));
}

void dict_button::ping_dict()
{
    emit dclicked(next);
}
