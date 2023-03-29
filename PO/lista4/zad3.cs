using System;
using System.Collections.Generic;

// vertices implemented as
// name and edges, which are 
// adjacent to this
public class Vertex{
    string vname;
    List<string> edges;

    public Vertex(string vname){
        this.vname = vname;
        edges = new List<string>();
    }

    public Vertex(string vname, List<string> edges){
        this.vname = vname;
        this.edges = edges;
    }


    public void Append(string new_v){
        edges.Add(new_v);
    }

}

// graph implemented as set of vertices
public class IGraph{
    List<Vertex> vertices;
    
    public void Is_neigh(string v1, string v2){
        
    }


}



public class Program{
    static void Main(){
        Console.WriteLine("adsf");

    }

}