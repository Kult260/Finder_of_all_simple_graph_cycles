#include <QtTest>
#include <windows.h>

#include <string>
#include "../circuitfinder.h"
#include "../directedgraph.h"
#include "../functions.h"
#include "../structs.h"
// add necessary includes here

class TESTS : public QObject
{
    Q_OBJECT

public:
    TESTS();
    ~TESTS();

private slots:
    void test_perform_coloring_for_vertices_from_the_corresponding_cycles_in_graph();
    void test_parseGraph();
    void test_create_map_with_vertices_of_graphand_their_numbers();
    void test_fill_map_with_values_and_their_numbers();
    void test_fill_adjacency_list_of_graph_with_vertex_numbers();
    void test_run();
    void test_replace_vertices_with_their_serial_numbers_in_adjacency_lists();
    void test_replace_vertex_numbers_with_corresponding_vertices_in_adjacency_lists();
    void test_remove_whitespace_except_new_line();
    void test_find_repeated_arc_in_cycles();
    void test_searching_for_substring_that_is_not_comment();
    void test_is_part_of_single_line_comment();
    void test_find_comment_positions();
    void test_convert_error_to_str();
    void test_validate_dot_graph_info();
    void test_read_text_file();
    void test_write_text_to_file();
};

TESTS::TESTS()
{

}

TESTS::~TESTS()
{

}

//************************* test_perform_coloring_for_vertices_from_the_corresponding_cycles_in_graph **************************

void TESTS::test_perform_coloring_for_vertices_from_the_corresponding_cycles_in_graph()
{

//--------------------------------Basic test----------------------------------
    std::string inp_graph_in_Dot =
"digraph G\n\
{\n\
1 -> 2;\n\
2 -> 3;\n\
3 -> 1;\n\
2 -> 4;\n\
4 -> 2;\n\
}";
    std::vector<std::list<int>> inp_list_with_simple_cycles = {{1, 2, 3, 1},{2, 4, 2} };
    std::string exp_inp_graph_in_Dot =
"digraph G\n\
{\n\
1->2[color=\"#FF00FF\"];\n\
2->3[color=\"#FF00FF\"];\n\
3->1[color=\"#FF00FF\"];\n\
2->4[color=\"#800080\"];\n\
4->2[color=\"#800080\"];\n\
}";

    perform_coloring_for_vertices_from_the_corresponding_cycles_in_graph(inp_graph_in_Dot,  inp_list_with_simple_cycles);
    std::string result = "\n" + exp_inp_graph_in_Dot + "\n" + inp_graph_in_Dot;
    QVERIFY2(inp_graph_in_Dot == exp_inp_graph_in_Dot, result.c_str());

//-------------------------------Repeating links in cycles-----------------------------------

   inp_graph_in_Dot =
"digraph G\n\
{\n\
1 -> 2;\n\
2 -> 3;\n\
3 -> 1;\n\
1 -> 3;\n\
3 -> 2;\n\
2 -> 1;\n\
}";
    inp_list_with_simple_cycles = {
        {1, 2, 3, 1},
        {1, 3, 2, 1}
    };

    exp_inp_graph_in_Dot =
"digraph G\n\
{\n\
1->2[color=\"#FF00FF\"];\n\
2->3[color=\"#FF00FF\"];\n\
3->1[color=\"#FF00FF\"];\n\
1->3[color=\"#800080\"];\n\
3->2[color=\"#800080\"];\n\
2->1[color=\"#800080\"];\n\
}";


    perform_coloring_for_vertices_from_the_corresponding_cycles_in_graph(inp_graph_in_Dot,  inp_list_with_simple_cycles);
    result = "\n" + exp_inp_graph_in_Dot + "\n" + inp_graph_in_Dot;
    QVERIFY2(inp_graph_in_Dot == exp_inp_graph_in_Dot, result.c_str());


//-------------------------------Long cycle-----------------------------------
   inp_graph_in_Dot =
"digraph G\n\
{\n\
1 -> 2;\n\
2 -> 3;\n\
3 -> 4;\n\
4 -> 5;\n\
5 -> 1;\n\
}";

    inp_list_with_simple_cycles = {
        {1, 2, 3, 4, 5, 1}
    };

    exp_inp_graph_in_Dot =
"digraph G\n\
{\n\
1->2[color=\"#FF00FF\"];\n\
2->3[color=\"#FF00FF\"];\n\
3->4[color=\"#FF00FF\"];\n\
4->5[color=\"#FF00FF\"];\n\
5->1[color=\"#FF00FF\"];\n\
}";


    perform_coloring_for_vertices_from_the_corresponding_cycles_in_graph(inp_graph_in_Dot,  inp_list_with_simple_cycles);
    result = "\n" + exp_inp_graph_in_Dot + "\n" + inp_graph_in_Dot;
    QVERIFY2(inp_graph_in_Dot == exp_inp_graph_in_Dot, result.c_str());

//-------------------------------one line comments-----------------------------------
   inp_graph_in_Dot =
"digraph G\n\
{\n\
1->2;//2 -> 3;\n\
2->3;// 3 -> 1;\n\
3->1;// 3 -> 1;\n\
}";

    inp_list_with_simple_cycles = {
        {1, 2, 3, 1}
    };

    exp_inp_graph_in_Dot =
"digraph G\n\
{\n\
1->2[color=\"#FF00FF\"];//2 -> 3;\n\
2->3[color=\"#FF00FF\"];// 3 -> 1;\n\
3->1[color=\"#FF00FF\"];// 3 -> 1;\n\
}";


    perform_coloring_for_vertices_from_the_corresponding_cycles_in_graph(inp_graph_in_Dot,  inp_list_with_simple_cycles);
    result = "\n" + exp_inp_graph_in_Dot + "\n" + inp_graph_in_Dot;
    QVERIFY2(inp_graph_in_Dot == exp_inp_graph_in_Dot, result.c_str());

//-------------------------------empty graph-----------------------------------
   inp_graph_in_Dot =
"digraph G\n\
{\n\
}";

    inp_list_with_simple_cycles = {};

    exp_inp_graph_in_Dot =
"digraph G\n\
{\n\
}";


    perform_coloring_for_vertices_from_the_corresponding_cycles_in_graph(inp_graph_in_Dot,  inp_list_with_simple_cycles);
    result = "\n" + exp_inp_graph_in_Dot + "\n" + inp_graph_in_Dot;
    QVERIFY2(inp_graph_in_Dot == exp_inp_graph_in_Dot, result.c_str());

//-------------------------------single nodes without cycles-----------------------------------

    inp_graph_in_Dot =
"digraph G\n\
{\n\
1;\n\
2;\n\
3;\n\
}";

    inp_list_with_simple_cycles = {};

    exp_inp_graph_in_Dot =
"digraph G\n\
{\n\
1;\n\
2;\n\
3;\n\
}";


        perform_coloring_for_vertices_from_the_corresponding_cycles_in_graph(inp_graph_in_Dot,  inp_list_with_simple_cycles);
    result = "\n" + exp_inp_graph_in_Dot + "\n" + inp_graph_in_Dot;
    QVERIFY2(inp_graph_in_Dot == exp_inp_graph_in_Dot, result.c_str());

//-------------------------------simple cycles that do not intersect each other-----------------------------------
    inp_graph_in_Dot =
        "digraph G\n\
    {\n\
            1 -> 2;\n\
            2 -> 3;\n\
            3 -> 1;\n\
            4 -> 5;\n\
            5 -> 6;\n\
            6 -> 4;\n\
    }";


        inp_list_with_simple_cycles = {
                                   {1, 2, 3, 1},
                                   {4, 5, 6, 4}
};

    exp_inp_graph_in_Dot =
"digraph G\n\
{\n\
1->2[color=\"#FF00FF\"];\n\
2->3[color=\"#FF00FF\"];\n\
3->1[color=\"#FF00FF\"];\n\
4->5[color=\"#800080\"];\n\
5->6[color=\"#800080\"];\n\
6->4[color=\"#800080\"];\n\
}";


        perform_coloring_for_vertices_from_the_corresponding_cycles_in_graph(inp_graph_in_Dot,  inp_list_with_simple_cycles);
    result = "\n" + exp_inp_graph_in_Dot + "\n" + inp_graph_in_Dot;
    QVERIFY2(inp_graph_in_Dot == exp_inp_graph_in_Dot, result.c_str());

//-------------------------------graph containing isolated nodes-----------------------------------

    inp_graph_in_Dot =
        "digraph G\n\
    {\n\
            1 -> 2;\n\
            2 -> 3;\n\
            3 -> 1;\n\
            4;\n\
            5;\n\
    }";

        inp_list_with_simple_cycles = {
                                   {1, 2, 3, 1}
};

    exp_inp_graph_in_Dot =
"digraph G\n\
{\n\
1->2[color=\"#FF00FF\"];\n\
2->3[color=\"#FF00FF\"];\n\
3->1[color=\"#FF00FF\"];\n\
4;\n\
5;\n\
}";
        perform_coloring_for_vertices_from_the_corresponding_cycles_in_graph(inp_graph_in_Dot,  inp_list_with_simple_cycles);
    result = "\n" + exp_inp_graph_in_Dot + "\n" + inp_graph_in_Dot;
    QVERIFY2(inp_graph_in_Dot == exp_inp_graph_in_Dot, result.c_str());

//-------------------------------graph containing cycles with different numbers of nodes-----------------------------------

    inp_graph_in_Dot =
        "digraph G\n\
    {\n\
        1 -> 2;\n\
        2 -> 3;\n\
        3 -> 4;\n\
        4 -> 1;\n\
        5 -> 6;\n\
        6 -> 5;\n\
    }";

        inp_list_with_simple_cycles = {
                                   {1, 2, 3, 4, 1},
                                   {5, 6, 5}

};

    exp_inp_graph_in_Dot =
"digraph G\n\
{\n\
1->2[color=\"#FF00FF\"];\n\
2->3[color=\"#FF00FF\"];\n\
3->4[color=\"#FF00FF\"];\n\
4->1[color=\"#FF00FF\"];\n\
5->6[color=\"#800080\"];\n\
6->5[color=\"#800080\"];\n\
}";
        perform_coloring_for_vertices_from_the_corresponding_cycles_in_graph(inp_graph_in_Dot,  inp_list_with_simple_cycles);
    result = "\n" + exp_inp_graph_in_Dot + "\n" + inp_graph_in_Dot;
    QVERIFY2(inp_graph_in_Dot == exp_inp_graph_in_Dot, result.c_str());


//-------------------------------flowers, more than in the prepared list-----------------------------------

    inp_graph_in_Dot =
"digraph G\n\
{\n\
1 -> 2;\n\
2 -> 3;\n\
3 -> 1;\n\
4 -> 5;\n\
5 -> 6;\n\
6 -> 4;\n\
7 -> 8;\n\
8 -> 9;\n\
9 -> 7;\n\
10 -> 11;\n\
11 -> 12;\n\
12 -> 10;\n\
13 -> 14;\n\
14 -> 15;\n\
15 -> 13;\n\
16 -> 17;\n\
17 -> 18;\n\
18 -> 16;\n\
19 -> 20;\n\
20 -> 21;\n\
21 -> 19;\n\
22 -> 23;\n\
23 -> 24;\n\
24 -> 22;\n\
25 -> 26;\n\
26 -> 27;\n\
27 -> 25;\n\
28 -> 29;\n\
29 -> 30;\n\
30 -> 28;\n\
31 -> 32;\n\
32 -> 33;\n\
33 -> 31;\n\
34 -> 35;\n\
35 -> 36;\n\
36 -> 34;\n\
37 -> 38;\n\
38 -> 39;\n\
39 -> 37;\n\
40 -> 41;\n\
41 -> 42;\n\
42 -> 40;\n\
43 -> 44;\n\
44 -> 45;\n\
45 -> 43;\n\
46 -> 47;\n\
47 -> 48;\n\
48 -> 46;\n\
49 -> 50;\n\
50 -> 51;\n\
51 -> 49;\n\
52 -> 53;\n\
53 -> 54;\n\
54 -> 52;\n\
55 -> 56;\n\
56 -> 57;\n\
57 -> 55;\n\
58 -> 59;\n\
59 -> 60;\n\
60 -> 58;\n\
}";

        inp_list_with_simple_cycles ={{1,2,3,1},
                                    {4,5,6,4},
                                    {7,8,9,7},
                                    {10,11,12,10},
                                    {13,14,15,13},
                                    {16,17,18,16},
                                    {19,20,21,19},
                                    {22,23,24,22},
                                    {25,26,27,25},
                                    {28,29,30,28},
                                    {31,32,33,31},
                                    {34,35,36,34},
                                    {37,38,39,37},
                                    {40,41,42,40},
                                    {43,44,45,43},
                                    {46,47,48,46},
                                    {49,50,51,49},
                                    {52,53,54,52},
                                    {55,56,57,55},
                                    {58,59,60,58}};

    exp_inp_graph_in_Dot =
"digraph G\n\
{\n\
1->2[color=\"#FF00FF\"];\n\
2->3[color=\"#FF00FF\"];\n\
3->1[color=\"#FF00FF\"];\n\
4->5[color=\"#800080\"];\n\
5->6[color=\"#800080\"];\n\
6->4[color=\"#800080\"];\n\
7->8[color=\"#FF0000\"];\n\
8->9[color=\"#FF0000\"];\n\
9->7[color=\"#FF0000\"];\n\
10->11[color=\"#800000\"];\n\
11->12[color=\"#800000\"];\n\
12->10[color=\"#800000\"];\n\
13->14[color=\"#FFFF00\"];\n\
14->15[color=\"#FFFF00\"];\n\
15->13[color=\"#FFFF00\"];\n\
16->17[color=\"#808000\"];\n\
17->18[color=\"#808000\"];\n\
18->16[color=\"#808000\"];\n\
19->20[color=\"#00FF00\"];\n\
20->21[color=\"#00FF00\"];\n\
21->19[color=\"#00FF00\"];\n\
22->23[color=\"#008000\"];\n\
23->24[color=\"#008000\"];\n\
24->22[color=\"#008000\"];\n\
25->26[color=\"#00FFFF\"];\n\
26->27[color=\"#00FFFF\"];\n\
27->25[color=\"#00FFFF\"];\n\
28->29[color=\"#008080\"];\n\
29->30[color=\"#008080\"];\n\
30->28[color=\"#008080\"];\n\
31->32[color=\"#0000FF\"];\n\
32->33[color=\"#0000FF\"];\n\
33->31[color=\"#0000FF\"];\n\
34->35[color=\"#000080\"];\n\
35->36[color=\"#000080\"];\n\
36->34[color=\"#000080\"];\n\
37->38[color=\"#D2691E\"];\n\
38->39[color=\"#D2691E\"];\n\
39->37[color=\"#D2691E\"];\n\
40->41[color=\"#FF4500\"];\n\
41->42[color=\"#FF4500\"];\n\
42->40[color=\"#FF4500\"];\n\
43->44[color=\"#00FF7F\"];\n\
44->45[color=\"#00FF7F\"];\n\
45->43[color=\"#00FF7F\"];\n\
46->47[color=\"#DEB887\"];\n\
47->48[color=\"#DEB887\"];\n\
48->46[color=\"#DEB887\"];\n\
49->50[color=\"#FF00FF\"];\n\
50->51[color=\"#FF00FF\"];\n\
51->49[color=\"#FF00FF\"];\n\
52->53[color=\"#800080\"];\n\
53->54[color=\"#800080\"];\n\
54->52[color=\"#800080\"];\n\
55->56[color=\"#FF0000\"];\n\
56->57[color=\"#FF0000\"];\n\
57->55[color=\"#FF0000\"];\n\
58->59[color=\"#800000\"];\n\
59->60[color=\"#800000\"];\n\
60->58[color=\"#800000\"];\n\
}";
        perform_coloring_for_vertices_from_the_corresponding_cycles_in_graph(inp_graph_in_Dot,  inp_list_with_simple_cycles);
    result = "\n" + inp_graph_in_Dot + "\n" + exp_inp_graph_in_Dot;
        QVERIFY2(QString::fromStdString(inp_graph_in_Dot) == QString::fromStdString(exp_inp_graph_in_Dot), result.c_str());

//-------------------------------cycle containing a loop-----------------------------------

    inp_graph_in_Dot =
        "digraph G\n\
    {\n\
        1 -> 1;\n\
    }";

        inp_list_with_simple_cycles = {
                                     {1,1}

};

    exp_inp_graph_in_Dot =
"digraph G\n\
{\n\
1->1[color=\"#FF00FF\"];\n\
}";
        perform_coloring_for_vertices_from_the_corresponding_cycles_in_graph(inp_graph_in_Dot,  inp_list_with_simple_cycles);
    result = "\n" + exp_inp_graph_in_Dot + "\n" + inp_graph_in_Dot;
    QVERIFY2(inp_graph_in_Dot == exp_inp_graph_in_Dot, result.c_str());

}



//************************* test_parseGraph **************************
void TESTS::test_parseGraph()
{

//--------------------------------Basic test----------------------------------
    std::string input_dotGraph  =
"digraph G\n\
{\n\
1 -> 2;\n\
2 -> 3;\n\
3 -> 1;\n\
}";

    DirectedGraph directed_graph_1(input_dotGraph);
    std::vector< std::pair<int, int> > inp_graph_arc_list = directed_graph_1.getGraphArcList();
    std::vector< std::list<int> > inp_adjacency_list = directed_graph_1.getGraphAdjacencyList();

    std::vector< std::pair<int, int> > exp_graph_arc_list = {{1, 2}, {2, 3}, {3, 1}};
    std::vector< std::list<int> > exp_adjacency_list = {{2}, {3}, {1}};

    QCOMPARE(inp_graph_arc_list, exp_graph_arc_list);
    QCOMPARE(inp_adjacency_list, exp_adjacency_list);

 //--------------------------------no connections----------------------------------

    input_dotGraph  =
        "digraph G\n\
    { \n\
        1;\n\
        2;\n\
        3;\n\
    }";

    DirectedGraph directed_graph_2(input_dotGraph);
    inp_graph_arc_list = directed_graph_2.getGraphArcList();
    inp_adjacency_list = directed_graph_2.getGraphAdjacencyList();

    exp_graph_arc_list = {{1,0},{2,0},{3,0}};
    exp_adjacency_list = {{}, {}, {}};

    QCOMPARE(inp_graph_arc_list, exp_graph_arc_list);
    QCOMPARE(inp_adjacency_list, exp_adjacency_list);

//--------------------------------contains one connection----------------------------------

    input_dotGraph  =
        "digraph G\n\
    { \n\
                1->2;\n\
    }";

        DirectedGraph directed_graph_3(input_dotGraph);
    inp_graph_arc_list = directed_graph_3.getGraphArcList();
    inp_adjacency_list = directed_graph_3.getGraphAdjacencyList();


    exp_graph_arc_list = {{1,2}};
    exp_adjacency_list = {{2}, {}};

    QCOMPARE(inp_graph_arc_list, exp_graph_arc_list);
    QCOMPARE(inp_adjacency_list, exp_adjacency_list);


//--------------------------------содержит висячие вершины----------------------------------

    input_dotGraph  =
        "digraph G\n\
    {\n\
            1 -> 2;\n\
            3;\n\
            4;\n\
    }";


        DirectedGraph directed_graph_4(input_dotGraph);
    inp_graph_arc_list = directed_graph_4.getGraphArcList();
    inp_adjacency_list = directed_graph_4.getGraphAdjacencyList();



    exp_graph_arc_list = {{1,2}, {3, 0}, {4,0}};
    exp_adjacency_list = {{2}, {}, {}, {}};

    QCOMPARE(inp_graph_arc_list, exp_graph_arc_list);
    QCOMPARE(inp_adjacency_list, exp_adjacency_list);


//--------------------------------содержит одну вершину----------------------------------

    input_dotGraph  =
        "digraph G\n\
    {\n\
                8;\n\
    }";


        DirectedGraph directed_graph_5(input_dotGraph);
    inp_graph_arc_list = directed_graph_5.getGraphArcList();
    inp_adjacency_list = directed_graph_5.getGraphAdjacencyList();


    exp_graph_arc_list = {{8,0}};
    exp_adjacency_list = {{}};

    QCOMPARE(inp_graph_arc_list, exp_graph_arc_list);
    QCOMPARE(inp_adjacency_list, exp_adjacency_list);

//--------------------------------много пробельных символов----------------------------------

    input_dotGraph  =
"digraph           G    \n\
{  \n\
    1 -> 2; \n\
     2      -> 3;   \n\
         3  ->    1; \n\
}";


    DirectedGraph directed_graph_6(input_dotGraph);
    inp_graph_arc_list = directed_graph_6.getGraphArcList();
    inp_adjacency_list = directed_graph_6.getGraphAdjacencyList();


    exp_graph_arc_list = {{1,2},{2,3},{3,1}};
    exp_adjacency_list = {{2},{3},{1}};

    QCOMPARE(inp_graph_arc_list, exp_graph_arc_list);
    QCOMPARE(inp_adjacency_list, exp_adjacency_list);


    //--------------------------------есть пустые строки----------------------------------

    input_dotGraph  =
        "digraph G\n\
    {\n\n 1 -> 2;\n\n 2 -> 3;\n\n}";



        DirectedGraph directed_graph_7(input_dotGraph);
    inp_graph_arc_list = directed_graph_7.getGraphArcList();
    inp_adjacency_list = directed_graph_7.getGraphAdjacencyList();


    exp_graph_arc_list = {{1,2},{2,3}};
    exp_adjacency_list = {{2},{3},{}};

    QCOMPARE(inp_graph_arc_list, exp_graph_arc_list);
    QCOMPARE(inp_adjacency_list, exp_adjacency_list);


 //--------------------------------значение вершин допустимо максимально---------------------------------

    input_dotGraph  =
"digraph G\n\
{\n\
2147483647 -> 1;\n\
}";



    DirectedGraph directed_graph_8(input_dotGraph);
    inp_graph_arc_list = directed_graph_8.getGraphArcList();
    inp_adjacency_list = directed_graph_8.getGraphAdjacencyList();



    for (auto const &arc : inp_graph_arc_list)
    {
        qDebug() << QString::number(arc.first) + "->" + QString::number(arc.second) + "\n";
    }

    for (auto const &current_list : inp_adjacency_list )
    {
        for(auto const &vertex : current_list)
        {
            qDebug() << QString::number(vertex) + ",";
        }

        qDebug() << "\n";
    }


    exp_graph_arc_list = {{2147483647,1}};
    exp_adjacency_list = {{}, {1}};

    for (auto const &arc : exp_graph_arc_list)
    {
        qDebug() << QString::number(arc.first) + "->" + QString::number(arc.second) + "\n";
    }

    for (auto const &current_list : exp_adjacency_list )
    {
        for(auto const &vertex : current_list)
        {
            qDebug() << QString::number(vertex) + ",";
        }

        qDebug() << "\n";
    }

    QCOMPARE(inp_graph_arc_list, exp_graph_arc_list);
    QCOMPARE(inp_adjacency_list, exp_adjacency_list);


    //--------------------------------значение вершин допустимо минимально---------------------------------

    input_dotGraph  =
        "digraph G\n\
    {\n\
                1 -> 1;\n\
    }";



        DirectedGraph directed_graph_9(input_dotGraph);
    inp_graph_arc_list = directed_graph_9.getGraphArcList();
    inp_adjacency_list = directed_graph_9.getGraphAdjacencyList();

    exp_graph_arc_list = {{1,1}};
    exp_adjacency_list = {{1}};

    QCOMPARE(inp_graph_arc_list, exp_graph_arc_list);
    QCOMPARE(inp_adjacency_list, exp_adjacency_list);

    //--------------------------------однострочный комментарий на отдельной строке---------------------------------

    input_dotGraph  =
        "digraph G \n\
    { \n\
        // This is a comment\n\
        1 -> 2;\n\
    }";




        DirectedGraph directed_graph_10(input_dotGraph);
    inp_graph_arc_list = directed_graph_10.getGraphArcList();
    inp_adjacency_list = directed_graph_10.getGraphAdjacencyList();

    exp_graph_arc_list = {{1,2}};
    exp_adjacency_list = {{2}, {}};

    QCOMPARE(inp_graph_arc_list, exp_graph_arc_list);
    QCOMPARE(inp_adjacency_list, exp_adjacency_list);

    //--------------------------------однострочный комментарий в строке со связью---------------------------------

    input_dotGraph  =
        "digraph G\n\
    { 1 -> 2; // This is a comment\n\
        2 -> 3;\n\
    }";





        DirectedGraph directed_graph_11(input_dotGraph);
    inp_graph_arc_list = directed_graph_11.getGraphArcList();
    inp_adjacency_list = directed_graph_11.getGraphAdjacencyList();

    exp_graph_arc_list = {{1,2}, {2,3}};
    exp_adjacency_list = {{2}, {3}, {}};

    QCOMPARE(inp_graph_arc_list, exp_graph_arc_list);
    QCOMPARE(inp_adjacency_list, exp_adjacency_list);

    //--------------------------------однострочный комментарий в строке со связью---------------------------------

    input_dotGraph  =
        "digraph G \n\
    { // Comment 1\n\
        1 -> 2; // Comment 2\n\
        2 -> 3; \n\
        // Comment 3\n\
        3 -> 1;\n\
    }";






        DirectedGraph directed_graph_12(input_dotGraph);
    inp_graph_arc_list = directed_graph_12.getGraphArcList();
    inp_adjacency_list = directed_graph_12.getGraphAdjacencyList();

    exp_graph_arc_list = {{1,2}, {2,3}, {3,1}};
    exp_adjacency_list = {{2}, {3}, {1}};

    QCOMPARE(inp_graph_arc_list, exp_graph_arc_list);
    QCOMPARE(inp_adjacency_list, exp_adjacency_list);
}


//************************* test_parseGraph **************************
void TESTS::test_create_map_with_vertices_of_graphand_their_numbers()
{

    //--------------------------------В строке не содержится пар со значениями----------------------------------
    std::string text_wit_value_pairs = "";
    std::string separator_between_values = "->";
    std::vector<std::pair<int, int>> vector_with_value_pairs;

    create_map_with_vertices_of_graphand_their_numbers(text_wit_value_pairs, separator_between_values, vector_with_value_pairs);

    std::vector< std::pair<int, int> > exp_vector_with_value_pairs = {};

    QCOMPARE(vector_with_value_pairs, exp_vector_with_value_pairs);

    //--------------------------------В строке одна пара значений----------------------------------
    text_wit_value_pairs = "1->2";
    separator_between_values = "->";
    vector_with_value_pairs = {};

    create_map_with_vertices_of_graphand_their_numbers(text_wit_value_pairs, separator_between_values, vector_with_value_pairs);

    exp_vector_with_value_pairs = {{1, 2}};

    QCOMPARE(vector_with_value_pairs, exp_vector_with_value_pairs);

    //--------------------------------В строке много пар значений----------------------------------
    text_wit_value_pairs =
"1->2\n\
3->4\n\
5->6";

    separator_between_values = "->";
    vector_with_value_pairs = {};

    create_map_with_vertices_of_graphand_their_numbers(text_wit_value_pairs, separator_between_values, vector_with_value_pairs);

    exp_vector_with_value_pairs = {{1, 2}, {3, 4}, {5, 6}};

    QCOMPARE(vector_with_value_pairs, exp_vector_with_value_pairs);

    //--------------------------------Разделитель состоит из одного символа----------------------------------
    text_wit_value_pairs = "1:2\n3:4\n5:6";
    separator_between_values = ":";
    vector_with_value_pairs = {};

    create_map_with_vertices_of_graphand_their_numbers(text_wit_value_pairs, separator_between_values, vector_with_value_pairs);

    exp_vector_with_value_pairs = {{1, 2}, {3, 4}, {5, 6}};

    QCOMPARE(vector_with_value_pairs, exp_vector_with_value_pairs);

    //--------------------------------Разделитель состоит из нескольких символов----------------------------------

    text_wit_value_pairs = "1<->2\n3<->4\n5<->6";
    separator_between_values = "<->";
    vector_with_value_pairs = {};

    create_map_with_vertices_of_graphand_their_numbers(text_wit_value_pairs, separator_between_values, vector_with_value_pairs);

    exp_vector_with_value_pairs = {{1, 2}, {3, 4}, {5, 6}};

    QCOMPARE(vector_with_value_pairs, exp_vector_with_value_pairs);


    //--------------------------------В строке есть пара допустимо максимальных значений----------------------------------

    text_wit_value_pairs = "2147483647->2147483647";
    separator_between_values = "->";
    vector_with_value_pairs = {};

    create_map_with_vertices_of_graphand_their_numbers(text_wit_value_pairs, separator_between_values, vector_with_value_pairs);

    exp_vector_with_value_pairs = {{2147483647, 2147483647}};

    QCOMPARE(vector_with_value_pairs, exp_vector_with_value_pairs);

}


void TESTS::test_fill_map_with_values_and_their_numbers()
{

    //--------------------------------Граф является пустым----------------------------------
    std::vector<std::pair<int, int>> graph_arc_list = {};
    std::map<int, int> map_of_graph_vertices_and_their_numbers = {};


    fill_map_with_values_and_their_numbers(map_of_graph_vertices_and_their_numbers, graph_arc_list);

    std::map<int, int> exp_map_of_graph_vertices_and_their_numbers = {};

    QCOMPARE(map_of_graph_vertices_and_their_numbers, exp_map_of_graph_vertices_and_their_numbers);


    //--------------------------------Граф содержит одну дугу----------------------------------
    graph_arc_list = {{1, 2}};
    map_of_graph_vertices_and_their_numbers = {};


    fill_map_with_values_and_their_numbers(map_of_graph_vertices_and_their_numbers, graph_arc_list);

    exp_map_of_graph_vertices_and_their_numbers = {{1, 1}, {2, 2}};

    QCOMPARE(map_of_graph_vertices_and_their_numbers, exp_map_of_graph_vertices_and_their_numbers);

    //--------------------------------Граф содержит много дуг----------------------------------
    graph_arc_list ={{1, 2}, {2, 3}, {6, 4}, {4, 5}};
    map_of_graph_vertices_and_their_numbers = {};


    fill_map_with_values_and_their_numbers(map_of_graph_vertices_and_their_numbers, graph_arc_list);

    exp_map_of_graph_vertices_and_their_numbers = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6,6}};

    QCOMPARE(map_of_graph_vertices_and_their_numbers, exp_map_of_graph_vertices_and_their_numbers);


    //--------------------------------Пары вершин в списке дуг изначально расположены по возрастанию вершин----------------------------------
    graph_arc_list ={{1, 3}, {2, 4}, {4, 5}};
    map_of_graph_vertices_and_their_numbers = {};


    fill_map_with_values_and_their_numbers(map_of_graph_vertices_and_their_numbers, graph_arc_list);

    exp_map_of_graph_vertices_and_their_numbers = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};

    QCOMPARE(map_of_graph_vertices_and_their_numbers, exp_map_of_graph_vertices_and_their_numbers);

    //--------------------------------Граф содержит дуги, включающие допустимо максимальные значения вершин----------------------------------
    graph_arc_list = {{2147483646, 2147483647}};
    map_of_graph_vertices_and_their_numbers = {};


    fill_map_with_values_and_their_numbers(map_of_graph_vertices_and_their_numbers, graph_arc_list);

    exp_map_of_graph_vertices_and_their_numbers = {{2147483646, 1}, {2147483647, 2}};

    QCOMPARE(map_of_graph_vertices_and_their_numbers, exp_map_of_graph_vertices_and_their_numbers);
}


void TESTS::test_fill_adjacency_list_of_graph_with_vertex_numbers()
{

    //--------------------------------Вершины в словаре эквивалентны их порядковым номерам----------------------------------
    std::map<int, int> map_of_graph_vertices_and_their_numbers = {{1, 1}, {2, 2}, {3, 3}, {4, 4}};
    std::vector<std::pair<int, int>> graph_arc_list = {{1, 2}, {2, 3}, {3, 4}};
    std::vector<std::list<int>> graph_adjacency_list = {};

    fill_adjacency_list_of_graph_with_vertex_numbers(map_of_graph_vertices_and_their_numbers, graph_arc_list, graph_adjacency_list);

    std::vector<std::list<int>> exp_graph_adjacency_list = {{2}, {3}, {4}, {}};

    QCOMPARE(graph_adjacency_list, exp_graph_adjacency_list);


    //--------------------------------В словаре не содержится вершин----------------------------------
    map_of_graph_vertices_and_their_numbers = {};
    graph_arc_list = {{1, 2}, {2, 3}, {3, 4}};
    graph_adjacency_list = {};

    fill_adjacency_list_of_graph_with_vertex_numbers(map_of_graph_vertices_and_their_numbers, graph_arc_list, graph_adjacency_list);

    exp_graph_adjacency_list = {};

    QCOMPARE(graph_adjacency_list, exp_graph_adjacency_list);


    //--------------------------------В словаре содержится одна вершина----------------------------------
    map_of_graph_vertices_and_their_numbers = {{1, 1}};
    graph_arc_list = {{1, 2}};
    graph_adjacency_list = {};

    fill_adjacency_list_of_graph_with_vertex_numbers(map_of_graph_vertices_and_their_numbers, graph_arc_list, graph_adjacency_list);

    exp_graph_adjacency_list = {{}};

    QCOMPARE(graph_adjacency_list, exp_graph_adjacency_list);

    //--------------------------------В словаре содержится много вершин----------------------------------
    map_of_graph_vertices_and_their_numbers = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
    graph_arc_list = {{1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 1}};
    graph_adjacency_list = {};

    fill_adjacency_list_of_graph_with_vertex_numbers(map_of_graph_vertices_and_their_numbers, graph_arc_list, graph_adjacency_list);

    exp_graph_adjacency_list = {{2}, {3}, {4}, {5}, {1}};

    QCOMPARE(graph_adjacency_list, exp_graph_adjacency_list);
}


void TESTS::test_run()
{

    //--------------------------------Простой граф с одним циклом----------------------------------
    std::vector<NodeList> Adjacency_list = { {2}, {3}, {1} };
    CircuitFinder curcuits1(Adjacency_list);
    std::vector< std:: list< int > >  list_with_simple_cycles = {};

    curcuits1.run(list_with_simple_cycles);

    std::vector<std::list<int>> exp_list_with_simple_cycles= {{1, 2, 3, 1}};

    QCOMPARE(list_with_simple_cycles, exp_list_with_simple_cycles);


    //--------------------------------Граф без циклов----------------------------------
    Adjacency_list = { {2, 3}, {3}, {} };
    CircuitFinder curcuits2(Adjacency_list);
    list_with_simple_cycles = {};

    curcuits2.run(list_with_simple_cycles);

    exp_list_with_simple_cycles= {};

    QCOMPARE(list_with_simple_cycles, exp_list_with_simple_cycles);


    //--------------------------------Граф с несколькими циклами----------------------------------
    Adjacency_list = {
        {2},        // Вершина 1 соединена с вершиной 2
        {3},        // Вершина 2 соединена с вершиной 3
        {1, 4},     // Вершина 3 соединена с вершинами 1 и 4
        {5},        // Вершина 4 соединена с вершиной 5
        {3}         // Вершина 5 соединена с вершиной 3 (образуются два цикла: {1, 2, 3, 1} и {3, 4, 5, 3})
    };

    CircuitFinder curcuits3(Adjacency_list);
    list_with_simple_cycles = {};

    curcuits3.run(list_with_simple_cycles);

    exp_list_with_simple_cycles= {{1, 2, 3, 1},{3, 4, 5, 3}};

    QCOMPARE(list_with_simple_cycles, exp_list_with_simple_cycles);

    //--------------------------------Граф с одним ребром----------------------------------
    Adjacency_list =
        { {2}, // Вершина 1 соединена с вершиной 2
            {} // Вершина 2 не имеет исходящих ребер
        };

    CircuitFinder curcuits4(Adjacency_list);
    list_with_simple_cycles = {};

    curcuits4.run(list_with_simple_cycles);

    exp_list_with_simple_cycles= {};

    QCOMPARE(list_with_simple_cycles, exp_list_with_simple_cycles);

    //--------------------------------Пустой граф----------------------------------
    Adjacency_list ={};

    CircuitFinder curcuits5(Adjacency_list);
    list_with_simple_cycles = {};

    curcuits5.run(list_with_simple_cycles);

    exp_list_with_simple_cycles= {};

    QCOMPARE(list_with_simple_cycles, exp_list_with_simple_cycles);

    //--------------------------------Граф с множеством циклов разной длины----------------------------------
    Adjacency_list ={
        {2, 3},         // Вершина 1 соединена с вершинами 2 и 3
        {3, 4},         // Вершина 2 соединена с вершинами 3 и 4
        {1, 4},         // Вершина 3 соединена с вершинами 1 и 4
        {5},            // Вершина 4 соединена с вершиной 5
        {1}             // Вершина 5 соединена с вершиной 1 (образуется цикл длины 3)
    };

    CircuitFinder curcuits6(Adjacency_list);
    list_with_simple_cycles = {};

    curcuits6.run(list_with_simple_cycles);

    exp_list_with_simple_cycles = {{1, 2, 3, 1}, {1, 2, 3, 4, 5, 1}, {1, 2, 4, 5, 1}, {1, 3, 1}, {1, 3, 4, 5, 1}};

    QCOMPARE(list_with_simple_cycles, exp_list_with_simple_cycles);

    //--------------------------------Граф с петлями и множеством циклов----------------------------------
    Adjacency_list ={
        {2},            // Вершина 1 соединена с вершиной 2 и 10
        {3},            // Вершина 2 соединена с вершиной 3
        {1, 4},         // Вершина 3 соединена с вершинами 1 и 4
        {6},         // Вершина 4 соединена с вершинами 6
        {1, 7},         // Вершина 5 соединена с вершинами 1 и 7
        {8, 6},            // Вершина 6 соединена с вершиной 8
        {9},            // Вершина 7 соединена с вершиной 9
        {5},            // Вершина 8 соединена с вершиной 5 (образуется цикл длины 3)
        {7},            // Вершина 9 соединена с вершиной 7
    };


    CircuitFinder curcuits7(Adjacency_list);
    list_with_simple_cycles = {};

    curcuits7.run(list_with_simple_cycles);

    exp_list_with_simple_cycles = {{1, 2, 3, 1}, {1, 2, 3, 4, 6, 8, 5, 1}, {6,6}, {7, 9, 7}};

    QCOMPARE(list_with_simple_cycles, exp_list_with_simple_cycles);


    //--------------------------------Большой граф с сложными путями и циклами----------------------------------
    Adjacency_list = {
        {2, 3, 4},      // Вершина 1 соединена с вершинами 2, 3 и 4
        {5, 6},         // Вершина 2 соединена с вершинами 5 и 6
        {7},            // Вершина 3 соединена с вершиной 7
        {1, 8},         // Вершина 4 соединена с вершинами 1 и 8
        {9},            // Вершина 5 соединена с вершиной 9
        {10},           // Вершина 6 соединена с вершиной 10
        {1},            // Вершина 7 соединена с вершиной 1 (образуется цикл длины 3)
        {2},            // Вершина 8 соединена с вершиной 2
        {4},            // Вершина 9 соединена с вершиной 4
    {5}             // Вершина 10 соединена с вершиной 5
};



    CircuitFinder curcuits8(Adjacency_list);
    list_with_simple_cycles = {};

    curcuits8.run(list_with_simple_cycles);

    exp_list_with_simple_cycles = {{1, 2, 5, 9, 4, 1}, {1, 3, 7, 1}, {2, 5, 9, 4, 8, 2}, {2, 6, 10, 5, 9, 4, 8, 2}};

    QCOMPARE(list_with_simple_cycles, exp_list_with_simple_cycles);


    //--------------------------------Граф с кратными связями----------------------------------
    Adjacency_list = {
        {2, 3, 4},      // Вершина 1 соединена с вершинами 2, 3 и 4
        {3, 5},         // Вершина 2 соединена с вершинами 3 и 5 (кратное ребро к вершине 3)
        {4},            // Вершина 3 соединена с вершиной 4
        {1},            // Вершина 4 соединена с вершиной 1
        {2, 6},         // Вершина 5 соединена с вершинами 2 и 6
        {1}             // Вершина 6 соединена с вершиной 1
    };




    CircuitFinder curcuits9(Adjacency_list);
    list_with_simple_cycles = {};

    curcuits9.run(list_with_simple_cycles);

    exp_list_with_simple_cycles = {{1, 2, 3, 4, 1}, {1, 2, 5, 6, 1}, {1, 3, 4, 1}, {1, 4, 1}, {2, 5, 2}};

    QCOMPARE(list_with_simple_cycles, exp_list_with_simple_cycles);

}

void TESTS::test_replace_vertices_with_their_serial_numbers_in_adjacency_lists()
{

    //--------------------------------В словаре и списке смежности отсутствуют вершины----------------------------------
   std::map<int, int> map_of_graph_vertices_and_their_numbers = {};
   std::vector<std::list<int>> graph_adjacency_list = {};

   std::vector<std::list<int>> inp_graph_adjacency_list = replace_vertices_with_their_serial_numbers_in_adjacency_lists(map_of_graph_vertices_and_their_numbers, graph_adjacency_list);

    std::vector<std::list<int>> exp_graph_adjacency_list = {};

    QCOMPARE(inp_graph_adjacency_list, exp_graph_adjacency_list);

    //--------------------------------В словаре и списке смежности есть одна вершина----------------------------------
    map_of_graph_vertices_and_their_numbers = {{1, 1}};
    graph_adjacency_list = {};

    inp_graph_adjacency_list = replace_vertices_with_their_serial_numbers_in_adjacency_lists(map_of_graph_vertices_and_their_numbers, graph_adjacency_list);

    exp_graph_adjacency_list = {};

    QCOMPARE(inp_graph_adjacency_list, exp_graph_adjacency_list);

    //--------------------------------Вершины в словаре эквивалентны их порядковым номерам----------------------------------
   map_of_graph_vertices_and_their_numbers = {{1, 1}, {2, 2}, {3, 3}, {4, 4}};
   graph_adjacency_list = {{2}, {3}, {4}, {}};

   inp_graph_adjacency_list = replace_vertices_with_their_serial_numbers_in_adjacency_lists(map_of_graph_vertices_and_their_numbers, graph_adjacency_list);

    exp_graph_adjacency_list = {{2}, {3}, {4}, {}};

    QCOMPARE(inp_graph_adjacency_list, exp_graph_adjacency_list);


    //--------------------------------Вершины в словаре эквивалентны их порядковым номерам----------------------------------
    map_of_graph_vertices_and_their_numbers = {{1, 1}, {2, 2}, {3, 3}, {4, 4}};
    graph_adjacency_list = {{2}, {3}, {4}, {}};

    inp_graph_adjacency_list = replace_vertices_with_their_serial_numbers_in_adjacency_lists(map_of_graph_vertices_and_their_numbers, graph_adjacency_list);

    exp_graph_adjacency_list = {{2}, {3}, {4}, {}};

    QCOMPARE(inp_graph_adjacency_list, exp_graph_adjacency_list);


    //--------------------------------Вершины в словаре не эквивалентны их порядковым номерам----------------------------------
    map_of_graph_vertices_and_their_numbers = {{10, 1}, {20, 2}, {30, 3}, {40, 4}};
    graph_adjacency_list = {{20}, {30}, {40}, {}};

    inp_graph_adjacency_list = replace_vertices_with_their_serial_numbers_in_adjacency_lists(map_of_graph_vertices_and_their_numbers, graph_adjacency_list);

    exp_graph_adjacency_list = {{2}, {3}, {4}, {}};

    QCOMPARE(inp_graph_adjacency_list, exp_graph_adjacency_list);
}


void TESTS::test_replace_vertex_numbers_with_corresponding_vertices_in_adjacency_lists()
{

    //--------------------------------В словаре и списке смежности отсутствуют вершины----------------------------------
    std::map<int, int> map_of_graph_vertices_and_their_numbers = {};
    std::vector<std::list<int>> graph_adjacency_list_with_vertex_numbers = {};


    std::vector<std::list<int>> inp_graph_adjacency_list_with_vertex_numbers = replace_vertex_numbers_with_corresponding_vertices_in_adjacency_lists(map_of_graph_vertices_and_their_numbers,  graph_adjacency_list_with_vertex_numbers);

    std::vector<std::list<int>> exp_graph_adjacency_list_with_vertex_numbers = {};

    QCOMPARE(graph_adjacency_list_with_vertex_numbers, exp_graph_adjacency_list_with_vertex_numbers);


    //--------------------------------В словаре и списке смежности есть одна вершина----------------------------------
    map_of_graph_vertices_and_their_numbers = {{1,1}};
    graph_adjacency_list_with_vertex_numbers = {};


    inp_graph_adjacency_list_with_vertex_numbers = replace_vertex_numbers_with_corresponding_vertices_in_adjacency_lists(map_of_graph_vertices_and_their_numbers,  graph_adjacency_list_with_vertex_numbers);

    exp_graph_adjacency_list_with_vertex_numbers = {};

    QCOMPARE(graph_adjacency_list_with_vertex_numbers, exp_graph_adjacency_list_with_vertex_numbers);

    //--------------------------------Вершины в словаре не эквивалентны их порядковым номерам----------------------------------
    map_of_graph_vertices_and_their_numbers = {{10, 1}, {20, 2}, {30, 3}, {40, 4}, {50, 5}};
    graph_adjacency_list_with_vertex_numbers = {{1}, {2}, {3}, {4}, {5}};


    inp_graph_adjacency_list_with_vertex_numbers = replace_vertex_numbers_with_corresponding_vertices_in_adjacency_lists(map_of_graph_vertices_and_their_numbers,  graph_adjacency_list_with_vertex_numbers);
    exp_graph_adjacency_list_with_vertex_numbers = {{10}, {20}, {30}, {40}, {50}};


    QCOMPARE(inp_graph_adjacency_list_with_vertex_numbers, exp_graph_adjacency_list_with_vertex_numbers);
    //--------------------------------Вершины в словаре эквивалентны их порядковым номерам----------------------------------
    map_of_graph_vertices_and_their_numbers = {{1, 1}, {2, 2}, {3, 3}, {4, 4}};
    graph_adjacency_list_with_vertex_numbers = {{1}, {2}, {3}, {4}};


    inp_graph_adjacency_list_with_vertex_numbers = replace_vertex_numbers_with_corresponding_vertices_in_adjacency_lists(map_of_graph_vertices_and_their_numbers,  graph_adjacency_list_with_vertex_numbers);
    exp_graph_adjacency_list_with_vertex_numbers = {{1}, {2}, {3}, {4}};

    for (auto const &current_list : inp_graph_adjacency_list_with_vertex_numbers )
    {
        for(auto const &vertex : current_list)
        {
            qDebug() << QString::number(vertex) + ",";
        }

        //qDebug() << "\n";
    }

    for (auto const &current_list : exp_graph_adjacency_list_with_vertex_numbers )
    {
        for(auto const &vertex : current_list)
        {
            qDebug() << QString::number(vertex) + ",";
        }

        //qDebug() << "\n";
    }


    QCOMPARE(inp_graph_adjacency_list_with_vertex_numbers, exp_graph_adjacency_list_with_vertex_numbers);

}

void TESTS::test_remove_whitespace_except_new_line()
{

    //--------------------------------Описание графа не содержит комментариев----------------------------------
    std::string inp_graph_in_Dot = "    digraph G {a -> b;}";

    remove_whitespace_except_new_line(inp_graph_in_Dot);

    std::string exp_graph_in_Dot = "digraph G{a->b;}";



    QCOMPARE(inp_graph_in_Dot, exp_graph_in_Dot);

    //--------------------------------Описание графа содержит один комментарий----------------------------------
    inp_graph_in_Dot = "digraph G{a -> b;// This is a comment\n}";;

    remove_whitespace_except_new_line(inp_graph_in_Dot);

    exp_graph_in_Dot = "digraph G{a->b;// This is a comment\n}";

    QCOMPARE(inp_graph_in_Dot, exp_graph_in_Dot);

    //--------------------------------Описание графа содержит много комментариев----------------------------------
    inp_graph_in_Dot = "digraph G{a -> b;// Comment 1\nc->d;// Comment 2\n}";

    remove_whitespace_except_new_line(inp_graph_in_Dot);

    exp_graph_in_Dot = "digraph G{a->b;// Comment 1\nc->d;// Comment 2\n}";

    QCOMPARE(inp_graph_in_Dot, exp_graph_in_Dot);

    //--------------------------------Комментарии находятся на отдельных строках----------------------------------
    inp_graph_in_Dot = "digraph G{\n// Comment 1\na -> b;\n// Comment 2\nc -> d;\n}";

    remove_whitespace_except_new_line(inp_graph_in_Dot);

    exp_graph_in_Dot = "digraph G{\n// Comment 1\na->b;\n// Comment 2\nc->d;\n}";

    QCOMPARE(inp_graph_in_Dot, exp_graph_in_Dot);

    //--------------------------------Комментарии находятся в строках со связями----------------------------------
    inp_graph_in_Dot = "digraph G{a -> b; // Comment 1\nc -> d; // Comment 2\n}";

    remove_whitespace_except_new_line(inp_graph_in_Dot);

    exp_graph_in_Dot = "digraph G{a->b;// Comment 1\nc->d;// Comment 2\n}";

    QCOMPARE(inp_graph_in_Dot, exp_graph_in_Dot);

    //--------------------------------Описание графа не содержит табуляций----------------------------------
    inp_graph_in_Dot = "digraph G{a -> b;c -> d;}";

    remove_whitespace_except_new_line(inp_graph_in_Dot);

    exp_graph_in_Dot = "digraph G{a->b;c->d;}";

    QCOMPARE(inp_graph_in_Dot, exp_graph_in_Dot);

    //--------------------------------Описание графа не содержит табуляций----------------------------------
    inp_graph_in_Dot = "digraph G{a -> b; c -> d;}";

    remove_whitespace_except_new_line(inp_graph_in_Dot);

    exp_graph_in_Dot = "digraph G{a->b;c->d;}";

    QCOMPARE(inp_graph_in_Dot, exp_graph_in_Dot);

    //--------------------------------Описание графа не содержит пробелов----------------------------------
    inp_graph_in_Dot = "digraph G{\n\ta->b;\n\tc->d;\n}";

    remove_whitespace_except_new_line(inp_graph_in_Dot);

    exp_graph_in_Dot = "digraph G{\na->b;\nc->d;\n}";

    QCOMPARE(inp_graph_in_Dot, exp_graph_in_Dot);
}

void TESTS::test_find_repeated_arc_in_cycles()
{

    //--------------------------------В списке циклов нет повторяющихся связей----------------------------------
    std::vector<std::list<int>> list_with_simple_cycles = {
        {1, 2, 3, 1},
        {4, 5, 6, 4}
    };

    std::set< std::pair<int, int> >  inp_list_with_simple_cycles = find_repeated_arc_in_cycles(list_with_simple_cycles);

    std::set<std::pair<int, int>> expected_result = {};

    QCOMPARE(inp_list_with_simple_cycles, expected_result);

    //--------------------------------В списке циклов одна повторяющаяся связь----------------------------------
    list_with_simple_cycles = { {1, 2, 3, 1}, {2, 3, 4, 2} };

    inp_list_with_simple_cycles = find_repeated_arc_in_cycles(list_with_simple_cycles);

    expected_result = {{2, 3}};

    QCOMPARE(inp_list_with_simple_cycles, expected_result);

    //--------------------------------В списке циклов много повторяющихся связей----------------------------------
    list_with_simple_cycles =  { {1, 2, 3, 1}, {2, 3, 1, 2} };

    inp_list_with_simple_cycles = find_repeated_arc_in_cycles(list_with_simple_cycles);

    expected_result = {{2, 3}, {3, 1}, {1, 2}};

    QCOMPARE(inp_list_with_simple_cycles, expected_result);

}

void TESTS::test_searching_for_substring_that_is_not_comment()
{

    //--------------------------------В строке содержится комментарий----------------------------------
    std::string input_str = "some text // comment\n";
    std::string substr = "text";
    size_t start_pos = 0;

    size_t inp_start_pos = searching_for_substring_that_is_not_comment(input_str, substr, start_pos);

    size_t expected_result = 9;

    QCOMPARE(inp_start_pos, expected_result);

    //--------------------------------В строке не содержится комментария----------------------------------
    input_str = "some text\n ";
    substr = "text";
    start_pos = 0;

    inp_start_pos = searching_for_substring_that_is_not_comment(input_str, substr, start_pos);

    expected_result = 9;

    QCOMPARE(inp_start_pos, expected_result);

    //--------------------------------Поиск начинается в части строки в комментарии----------------------------------
    input_str = "some text // comment text\n";
    substr = "comment";
    start_pos = 0;

    inp_start_pos = searching_for_substring_that_is_not_comment(input_str, substr, start_pos);

    expected_result = std::string::npos;

    qDebug() << QString::number(inp_start_pos);

    QCOMPARE(inp_start_pos, expected_result);

    //--------------------------------Поиск начинается с первого символа заголовка комментария----------------------------------
    input_str = "some text // comment\n ";
    substr = "/";
    start_pos = 0;

    inp_start_pos = searching_for_substring_that_is_not_comment(input_str, substr, start_pos);

    expected_result = std::string::npos;

    QCOMPARE(inp_start_pos, expected_result);

    //--------------------------------В строке присутствует много комментариев----------------------------------
    input_str = "some text // first comment\nmore text // second comment";
    substr = "text";
    start_pos = 0;

    inp_start_pos = searching_for_substring_that_is_not_comment(input_str, substr, start_pos);

    expected_result = 9;

    QCOMPARE(inp_start_pos, expected_result);

    //--------------------------------Комментарии расположены на отдельных строках----------------------------------
    input_str = "some text\n// comment\nmore text";
    substr = "text";
    start_pos = 0;

    inp_start_pos = searching_for_substring_that_is_not_comment(input_str, substr, start_pos);

    expected_result = 9;

    QCOMPARE(inp_start_pos, expected_result);

    //--------------------------------Комментарии не расположены на отдельных строках----------------------------------
    input_str = "some text // comment\nmore text // another comment";
    substr = "text";
    start_pos = 0;

    inp_start_pos = searching_for_substring_that_is_not_comment(input_str, substr, start_pos);

    expected_result = 9;

    QCOMPARE(inp_start_pos, expected_result);

}

void TESTS::test_is_part_of_single_line_comment()
{

    //--------------------------------Поиск начинается в части строки в комментарии----------------------------------
    std::string input_str = "some text // comment";
    size_t end_pos = 10;

    size_t inp_result = is_part_of_single_line_comment(input_str, end_pos);

    bool expected_result = true;

    QCOMPARE(inp_result, expected_result);

    //--------------------------------Поиск начинается в части строки до комментария----------------------------------
    input_str = "some text // comment";
    end_pos = 8;

    inp_result = is_part_of_single_line_comment(input_str, end_pos);

     expected_result = false;

    QCOMPARE(inp_result, expected_result);

     //--------------------------------Поиск начинается с первого символа заголовка комментария----------------------------------
     input_str = "// comment\nsome text";
     end_pos = 2;

     inp_result = is_part_of_single_line_comment(input_str, end_pos);

     expected_result = true;

     QCOMPARE(inp_result, expected_result);

     //--------------------------------Поиск начинается с последнего символа строки----------------------------------
     input_str = "some text // comment";
     end_pos = input_str.size();

     inp_result = is_part_of_single_line_comment(input_str, end_pos);

     expected_result = true;

     QCOMPARE(inp_result, expected_result);

}

void TESTS::test_find_comment_positions()
{

    //--------------------------------Текст не содержит комментариев----------------------------------
    std::string input_str = "This is a text without comments";

    std::vector<size_t>  inp_result = find_comment_positions(input_str);

    std::vector<size_t> expected_result = {};

    QCOMPARE(inp_result, expected_result);

    //--------------------------------Текст содержит один комментарий----------------------------------
    input_str = "This is a text with // one comment";

    inp_result = find_comment_positions(input_str);

    expected_result = {20};

    QCOMPARE(inp_result, expected_result);

    //--------------------------------Текст содержит много комментариев----------------------------------
    input_str = "This \n// is \n // a \n // text\n // with \n // many \n // comments";

    inp_result = find_comment_positions(input_str);

    expected_result = {6, 14, 21, 30, 40, 50};

    QCOMPARE(inp_result, expected_result);

    //--------------------------------Комментарии находятся на отдельных строках----------------------------------
    input_str = "// Comment 1\n// Comment 2\n// Comment 3";

    inp_result = find_comment_positions(input_str);

    expected_result = {0, 13, 26};



    QCOMPARE(inp_result, expected_result);

    //--------------------------------Комментарии находятся не на отдельных строках----------------------------------
    input_str = "Text // Comment 1\n with // Comment 2\n without // Comment 3\n new line";

    inp_result = find_comment_positions(input_str);

    expected_result = {5, 24, 46};

    QCOMPARE(inp_result, expected_result);
}

void TESTS::test_convert_error_to_str()
{

    //--------------------------------Неверно указан файл с входными данными. Возможно, файл не существует.----------------------------------
    Error error = {INVALID_OPEN_FILE, 0};

    std::string inp_result = convert_error_to_str(error);

    std::string expected_result = "\nНеверно указан файл с входными данными. Возможно, файл не существует.";

    QCOMPARE(inp_result, expected_result);

    //--------------------------------Неверно указанно ключевое слово графа или оно отсутствует. Возможно, допущена ошибка в ключевом слове----------------------------------
    error = {INVALID_KEYWORD, 0};

    inp_result = convert_error_to_str(error);

    expected_result = "\nНеверно указанно ключевое слово графа или оно отсутствует. Возможно, допущена ошибка в ключевом слове или оно отсутствует.";;

    QCOMPARE(inp_result, expected_result);


    //--------------------------------Во входном файле отсутствует имя графа или оно содержит недопустимые символы. ----------------------------------
    error = {INVALID_HEADER, 0};

    inp_result = convert_error_to_str(error);

    expected_result = "\nВо входном файле отсутствует имя графа или оно содержит недопустимые символы.";

    QCOMPARE(inp_result, expected_result);

    //--------------------------------Границы, в которых описан граф, не определены.  ----------------------------------
    error = {INVALID_CURLY_BRACES, 0};

    inp_result = convert_error_to_str(error);

    expected_result = "\nГраницы, в которых описан граф, не определены. Возможно, во входном файле отсутствует одна из фигурных скобок или она расположена не на отдельной строке.";;

    QCOMPARE(inp_result, expected_result);


    //--------------------------------В промежутке между строкой с ключевым словом и именем графа и строкой с первой фигурной скобкой содержатся лишние символы. ----------------------------------
    error = {INVALID_SPACE_BETWEEN_HEADING_AND_CURLY_BRACKET, 0};

    inp_result = convert_error_to_str(error);

    expected_result = "\nВ промежутке между строкой с ключевым словом и именем графа и строкой с первой фигурной скобкой содержатся лишние символы.";

    QCOMPARE(inp_result, expected_result);

    //--------------------------------В одной из строк, описывающих связи графа, входного файла содержится более двух вершин или содержатся лишние символы. ----------------------------------
    error = {INVALID_COMMUNICATION_BETWEEN_VERTICES, 0};

    inp_result = convert_error_to_str(error);

    expected_result = "\nВ одной из строк, описывающих связи графа, входного файла содержится более двух вершин или содержатся лишние символы.\nСтрока:0.";

    QCOMPARE(inp_result, expected_result);

    //--------------------------------Описание графа содержит недопустимые символы или недопустимое имя вершины в одной из строк в описании графа. ----------------------------------
    error = {INVALID_VERTICE_NAME_OR_SYMBOLS, 0};

    inp_result = convert_error_to_str(error);

    expected_result = "\nОписание графа содержит недопустимые символы или недопустимое имя вершины в одной из строк в описании графа.\nСтрока:0.";

    QCOMPARE(inp_result, expected_result);

    //--------------------------------Описание графа содержит недопустимые символы или недопустимое имя вершины в одной из строк в описании графа. ----------------------------------
    error = {SEMOLON_IS_MISSING, 0};

    inp_result = convert_error_to_str(error);

    expected_result = "\nВ одной из строк с описанием графа не определено окончание. Возможно, в строке отсутствует символ точки с запятой.\nСтрока:0.";

    QCOMPARE(inp_result, expected_result);

    //--------------------------------В графе содержится неопознанная связь. В одной из строк с описанием графа связь между вершинами отсутствует либо указана некорректно. ----------------------------------
    error = {INVALID_CONNECTION_SIGN, 0};

    inp_result = convert_error_to_str(error);

    expected_result =  "\nВ графе содержится неопознанная связь. В одной из строк с описанием графа связь между вершинами отсутствует либо указана некорректно.\nСтрока:0.";

    QCOMPARE(inp_result, expected_result);

    //--------------------------------После описания графа обнаружена лишняя запись. В файле должно содержаться описание только одного графа. ----------------------------------
    error = {INVALID_SYMBOLS_AFTER_GRAPH_DESCRIPTION, 0};

    inp_result = convert_error_to_str(error);

    expected_result =  "\nПосле описания графа обнаружена лишняя запись. В файле должно содержаться описание только одного графа.";

    QCOMPARE(inp_result, expected_result);

    //--------------------------------После описания графа обнаружена лишняя запись. В файле должно содержаться описание только одного графа. ----------------------------------
    error = {INVALID_SAVE_FILE, 0};

    inp_result = convert_error_to_str(error);

    expected_result =  "\nНе удалось сохранить файл для записи результата. Возможно, путь для сохранения или имя файла указаны некорректно.";

    QCOMPARE(inp_result, expected_result);
}

void TESTS::test_validate_dot_graph_info()
{

    //--------------------------------Неверное ключевое слово и имя----------------------------------
    std::string dot_info = "  graph";
    std::vector<Error> inp_errors = {};

    validate_dot_graph_info(dot_info, inp_errors);

    std::vector<Error> exp_errors = {{INVALID_KEYWORD,0}};


    QCOMPARE(inp_errors, exp_errors);

    //--------------------------------Неверное имя----------------------------------
    dot_info = "  digraph 1G";
    inp_errors = {};

    validate_dot_graph_info(dot_info, inp_errors);

    exp_errors = {{INVALID_HEADER,0}};

    qDebug() << QString::number(inp_errors[0].type);
    qDebug() << QString::number(exp_errors[0].type);
    QCOMPARE(inp_errors, exp_errors);

    //--------------------------------Лишние символы в пространстве между первой фигурной скобкой и именем----------------------------------
    dot_info = "  digraph G sfsf { }";
    inp_errors = {};

    validate_dot_graph_info(dot_info, inp_errors);

    exp_errors = {{INVALID_SPACE_BETWEEN_HEADING_AND_CURLY_BRACKET,0}};

    qDebug() << QString::number(inp_errors[0].type);
    qDebug() << QString::number(exp_errors[0].type);

    QCOMPARE(inp_errors, exp_errors);

    //--------------------------------Неверное расположение первой фигурной скобки в строке----------------------------------
    dot_info =  "  digraph G\n\
    { 1;";
    inp_errors = {};

    validate_dot_graph_info(dot_info, inp_errors);

    exp_errors = {{INVALID_CURLY_BRACES,0}};


    QCOMPARE(inp_errors, exp_errors);

    //--------------------------------Нет описания----------------------------------
    dot_info =  "";
    inp_errors = {};

        validate_dot_graph_info(dot_info, inp_errors);

        exp_errors = {{INVALID_KEYWORD,0}};


        QCOMPARE(inp_errors, exp_errors);

    //--------------------------------Неверное имя и ключевое слово графа----------------------------------
        dot_info =  "  graph 1G";
        inp_errors = {};

        validate_dot_graph_info(dot_info, inp_errors);

        exp_errors = {{INVALID_KEYWORD,0}};


        QCOMPARE(inp_errors, exp_errors);

    //--------------------------------Неверное расположение фигурной скобки и много связей в одной строке----------------------------------
    dot_info =
"  digraph G \n\
{ 1;\n\
        1->2->;";

    inp_errors = {};

    validate_dot_graph_info(dot_info, inp_errors);

    exp_errors = {{INVALID_CURLY_BRACES,0}};


    QCOMPARE(inp_errors, exp_errors);

    //--------------------------------Лишняя связь в описании графа----------------------------------
    dot_info = "  digraph G\n\
    { \n\
        1;\n\
        1->2->2;\n\
}";


            inp_errors = {};

        validate_dot_graph_info(dot_info, inp_errors);

        exp_errors = {{INVALID_COMMUNICATION_BETWEEN_VERTICES, 4}};


        QCOMPARE(inp_errors, exp_errors);

        //--------------------------------Много связей в одной строке и неверный символ в описании графа----------------------------------
        dot_info = "  digraph G\n\
        { \n\
            1;\n\
            A->2->2;\n\
        }";


            inp_errors = {};

        validate_dot_graph_info(dot_info, inp_errors);

            exp_errors = {{ INVALID_VERTICE_NAME_OR_SYMBOLS, 4}};


        QCOMPARE(inp_errors, exp_errors);

    //--------------------------------Отсутствует точка с запятой в описании графа----------------------------------
    dot_info =  "  digraph G\n\
        {\n\
        1;\n\
        1->2\n\
        }";



    inp_errors = {};

    validate_dot_graph_info(dot_info, inp_errors);

    exp_errors = {{SEMOLON_IS_MISSING, 4}};

    qDebug() << QString::number(inp_errors[0].type);
    qDebug() << QString::number(exp_errors[0].type);

    QCOMPARE(inp_errors, exp_errors);

    //--------------------------------Много связей в одной строке, отсутствует точка с запятой в описании графа----------------------------------
    dot_info =  "  digraph G\n\
    { \n\
        1;\n\
        1->-2->2\n\
    }";



        inp_errors = {};

    validate_dot_graph_info(dot_info, inp_errors);

        exp_errors = {{INVALID_COMMUNICATION_BETWEEN_VERTICES, 4}};


    QCOMPARE(inp_errors, exp_errors);

        //--------------------------------Неопознанная связь в описании графа----------------------------------
        dot_info =  "  digraph G\n\
        { \n\
            1;\n\
            1 - 2;\n\
        }";

            inp_errors = {};

        validate_dot_graph_info(dot_info, inp_errors);

        exp_errors = {{INVALID_CONNECTION_SIGN, 4}};

        QCOMPARE(inp_errors, exp_errors);

        //--------------------------------Лишние символы после описания графа----------------------------------
        dot_info =  "   digraph G\n\
        { \n\
        1;\n\
        1->2;\n\
        }\n\
        \n\
        grgrgr";


            inp_errors = {};

        validate_dot_graph_info(dot_info, inp_errors);

        exp_errors = {{INVALID_SYMBOLS_AFTER_GRAPH_DESCRIPTION,0}};


        QCOMPARE(inp_errors, exp_errors);

        //--------------------------------Отсутствует открывающая фигурная скобка в описании графа----------------------------------
        dot_info =  "   digraph G\n\
            1;\n\
            1->2;\n\
        }\n";


            inp_errors = {};

        validate_dot_graph_info(dot_info, inp_errors);

        exp_errors = {{INVALID_CURLY_BRACES,0}};

        QCOMPARE(inp_errors, exp_errors);

        //--------------------------------Отсутствует закрывающая фигурная скобка в описании графа----------------------------------
        dot_info =  "   digraph G\n\
            }\n\
            1;\n\
            1->2;\n";


    inp_errors = {};

validate_dot_graph_info(dot_info, inp_errors);

exp_errors = {{INVALID_CURLY_BRACES,0}};


QCOMPARE(inp_errors, exp_errors);


}


void TESTS::test_read_text_file()
{

//--------------------------------Путь к существующему файлу----------------------------------
std::string file_path = ".//home//user//test_files//existing_file.txt";
std::string text_of_file = "";
std::vector<Error> errors = {};

bool inp_open_flag = read_text_file(file_path, text_of_file, errors);

std::string exp_text_of_file = "";
std::vector<Error> exp_errors = {};
bool exp_open_flag = true;

QCOMPARE(text_of_file, exp_text_of_file);
QCOMPARE(inp_open_flag, exp_open_flag);
QCOMPARE(errors, exp_errors);

//--------------------------------Путь к несуществующему файлу----------------------------------
file_path = ".//test_files//nonexistent_file.txt";
text_of_file = "";
errors = {};

inp_open_flag = read_text_file(file_path, text_of_file, errors);

exp_text_of_file = "";
exp_errors = {{INVALID_OPEN_FILE,0}};
exp_open_flag = false;

QCOMPARE(text_of_file, exp_text_of_file);
QCOMPARE(inp_open_flag, exp_open_flag);
QCOMPARE(errors, exp_errors);

//--------------------------------Существующий файл с некорректным расширением----------------------------------
file_path = ".//test_files//existing_file.shfskq";
text_of_file = "";
errors = {};

inp_open_flag = read_text_file(file_path, text_of_file, errors);

exp_text_of_file = "";
exp_errors = {};
exp_open_flag = true;

QCOMPARE(text_of_file, exp_text_of_file);
QCOMPARE(inp_open_flag, exp_open_flag);
QCOMPARE(errors, exp_errors);

//--------------------------------Длинный путь к файлу с длинным именем----------------------------------
file_path = ".//test_files//very_long_directory_name//another_long_directory_name//some_really_long_file_name_that_sems_to_go_on_forever.txt";
text_of_file = "";
errors = {};

inp_open_flag = read_text_file(file_path, text_of_file, errors);

exp_text_of_file = "";
exp_errors = {};
exp_open_flag = true;

QCOMPARE(text_of_file, exp_text_of_file);
QCOMPARE(inp_open_flag, exp_open_flag);
QCOMPARE(errors, exp_errors);

//--------------------------------Короткий путь к файлу с коротким именем----------------------------------
file_path = "./a.txt";
text_of_file = "";
errors = {};

inp_open_flag = read_text_file(file_path, text_of_file, errors);

exp_text_of_file = "";
exp_errors = {};
exp_open_flag = true;

QCOMPARE(text_of_file, exp_text_of_file);
QCOMPARE(inp_open_flag, exp_open_flag);
QCOMPARE(errors, exp_errors);


//--------------------------------Путь к файлу содержит кириллицу----------------------------------
file_path = "./тестовые_файлы/t.txt";
text_of_file = "";
errors = {};

inp_open_flag = read_text_file(file_path, text_of_file, errors);

exp_text_of_file = "";
exp_errors = {};
exp_open_flag = true;

QCOMPARE(text_of_file, exp_text_of_file);
QCOMPARE(inp_open_flag, exp_open_flag);
QCOMPARE(errors, exp_errors);

//--------------------------------Имя файла содержит кириллицу----------------------------------
file_path = "./test_files/существующий_файл.txt";
text_of_file = "";
errors = {};

inp_open_flag = read_text_file(file_path, text_of_file, errors);

exp_text_of_file = "";
exp_errors = {};
exp_open_flag = true;

QCOMPARE(text_of_file, exp_text_of_file);
QCOMPARE(inp_open_flag, exp_open_flag);
QCOMPARE(errors, exp_errors);

}


void TESTS::test_write_text_to_file()
{

//--------------------------------Стандартный путь для сохранения----------------------------------
std::string save_path = "./home/user/test_files/save_file.dot";
std::string text_to_write = "digraph { a -> b; }";
std::vector<Error> errors = {};

bool inp_save_flag = write_text_to_file(save_path, text_to_write, errors);

std::vector<Error> exp_errors = {};
bool exp_save_flag = true;

QCOMPARE(inp_save_flag, exp_save_flag);
QCOMPARE(errors, exp_errors);

//--------------------------------Имя сохраняемого файла содержит недопустимые символы----------------------------------
save_path = "./test_files/invalid:name.dot";
text_to_write = " digraph { a -> b; }";
errors = {};

inp_save_flag = write_text_to_file(save_path, text_to_write, errors);

exp_errors = {{INVALID_SAVE_FILE,0}};
exp_save_flag = false;

QCOMPARE(inp_save_flag, exp_save_flag);
QCOMPARE(errors, exp_errors);

//--------------------------------Файл с таким именем уже имеется в директории----------------------------------
save_path = "./test_files/existing_file.dot";
text_to_write = " digraph { a -> b; }";
errors = {};

inp_save_flag = write_text_to_file(save_path, text_to_write, errors);

exp_errors = {};
exp_save_flag = true;

QCOMPARE(inp_save_flag, exp_save_flag);
QCOMPARE(errors, exp_errors);

//--------------------------------Расширение файла является некорректным----------------------------------
save_path = "./test_files/save_file.rggrrgr";
text_to_write = " digraph { a -> b; }";
errors = {};

inp_save_flag = write_text_to_file(save_path, text_to_write, errors);

exp_errors = {};
exp_save_flag = true;

QCOMPARE(inp_save_flag, exp_save_flag);
QCOMPARE(errors, exp_errors);

//--------------------------------Длинный путь для сохранения и длинное имя файла----------------------------------
save_path = ".//test_files//very_long_directory_name//another_long_directory_name//some_really_long_file_name_that_seems_to_go_on_forever.dot";
text_to_write = " digraph { a -> b; }";
errors = {};

inp_save_flag = write_text_to_file(save_path, text_to_write, errors);

exp_errors = {};
exp_save_flag = true;

QCOMPARE(inp_save_flag, exp_save_flag);
QCOMPARE(errors, exp_errors);

//--------------------------------Короткий путь для сохранения и короткое имя файла----------------------------------
save_path = "./b.dot";
text_to_write = " digraph { a -> b; }";
errors = {};

inp_save_flag = write_text_to_file(save_path, text_to_write, errors);

exp_errors = {};
exp_save_flag = true;

QCOMPARE(inp_save_flag, exp_save_flag);
QCOMPARE(errors, exp_errors);

//--------------------------------Путь сохранения содержит кириллицу----------------------------------
save_path = "./тестовые_файлы/save_file.dot";
text_to_write = " digraph { a -> b; }";
errors = {};

inp_save_flag = write_text_to_file(save_path, text_to_write, errors);

exp_errors = {};
exp_save_flag = true;

QCOMPARE(inp_save_flag, exp_save_flag);
QCOMPARE(errors, exp_errors);

//--------------------------------Имя файла содержит кириллицу----------------------------------
save_path = "./test_files/сохранить_файл.dot";
text_to_write = " digraph { a -> b; }";
errors = {};

inp_save_flag = write_text_to_file(save_path, text_to_write, errors);

exp_errors = {};
exp_save_flag = true;

QCOMPARE(inp_save_flag, exp_save_flag);
QCOMPARE(errors, exp_errors);

//--------------------------------Сохранение файла по несуществующему пути----------------------------------
save_path = "./backup/MyGraph.dot";
text_to_write = " digraph { a -> b; }";
errors = {};

inp_save_flag = write_text_to_file(save_path, text_to_write, errors);

exp_errors = {{INVALID_SAVE_FILE,0}};
exp_save_flag = false;

QCOMPARE(inp_save_flag, exp_save_flag);
QCOMPARE(errors, exp_errors);
}

QTEST_APPLESS_MAIN(TESTS)

#include "tst_tests.moc"
