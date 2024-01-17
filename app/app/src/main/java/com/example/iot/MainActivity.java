package com.example.iot;

import static java.lang.System.in;
import static java.lang.System.out;
import static java.lang.Thread.sleep;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Context;
import android.graphics.Color;
import android.os.Bundle;
import android.text.TextUtils;
import android.util.Log;
import android.view.Gravity;
import android.view.View;
import android.widget.Button;
import android.widget.TableLayout;
import android.widget.TableRow;
import android.widget.TextView;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.Socket;
import java.util.Objects;

public class MainActivity extends AppCompatActivity {

    private TextView info;
    private TextView ip;

    private Button conect;
    private Button result;

    public Socket client;
    public DataOutputStream out;
    public DataInputStream in;

    public TableLayout table;

    public static Context context;

    String allinf = "";
    String allinf2 = "a";
    String inf = "1";
    int connection = 0;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        context = getApplicationContext();

        info = findViewById(R.id.info);

        ip = findViewById(R.id.ipText);

        conect = findViewById(R.id.button_connect);
        result = findViewById(R.id.button_result);
        table = findViewById(R.id.tableInfo);
        //info.setText("Соединение установлено");


        conect.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                    new Thread(new Runnable(){
                        public void run(){
                            try
                            {
                                String ipt = ip.getText().toString();
                                System.out.print(ipt);
                                Log.d(ipt,ipt);
                                client = new Socket(ipt, 1230);
                                out = new DataOutputStream(client.getOutputStream());
                                in = new DataInputStream(client.getInputStream());
                                out.write("2".getBytes());
                                connection = 0;
                            }
                            catch (IOException e)
                            {
                                e.printStackTrace();
                                info.setText(e.getMessage());
                                connection=-1;
                            }
                        }
                    }).start();

                try {
                    Thread.sleep(2500);
                    } catch (InterruptedException e) {
                    throw new RuntimeException(e);
                    }

                    if(connection!=-1) {
                        info.setText("Соединение установлено");
                        connection = 1;
                    }
            }
        });

        result.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (connection == 1) {
                    new Thread(new Runnable() {
                        public void run() {
                            try
                            {
                                out.write("1".getBytes());

                                byte buf_out[] = new byte[256];
                                allinf = "";

                                while (inf != "") {
                                    //info.setText(allinf2);
                                    in.read(buf_out);

                                    //inf = new String(buf_out);

                                    inf = ((new String(buf_out)).split("\n"))[0].replaceAll("\\s+", " ");

                                    //allinf2 = allinf2 + "1";

                                    allinf = allinf + inf + "\n";

                                    inf = inf.replaceAll("\\s+", " ");
                                    inf = inf.replaceFirst(" ", "");
                                    String[] words = inf.split(" ");
                                    int num = 1;



                                    /*for (String word : words) {
                                        if (Objects.equals(word, "*")) {
                                            num--;
                                        }
                                        num++;
                                        allinf = allinf + word + "\n";
                                        if (num == 8) {
                                            break;
                                        }
                                    }*/

                                }
                                //client.close();
                            }
                        catch (IOException e)
                        {
                            info.setText(e.getMessage());
                        }
                        }
                    }).start();

                    try {
                        Thread.sleep(2000);
                    } catch (InterruptedException e) {
                        throw new RuntimeException(e);
                    }
                    //info.setText(allinf2);
                    /*allinf = "   netdatacomm_local  Infra   6     54 Mbit/s  37      ▂▄__  WEP\n" +
                            "*  F1                 Infra   11    54 Mbit/s  98      ▂▄▆█  WPA1\n" +
                            "   LoremCorp          Infra   1     54 Mbit/s  62      ▂▄▆_  WPA2\n" +
                            "   Internet           Infra   6     54 Mbit/s  29      ▂___  WPA1\n" +
                            "   HPB110a.F2672A     Ad-Hoc  6     54 Mbit/s  22      ▂___  --\n" +
                            "   Jozinet            Infra   1     54 Mbit/s  19      ▂___  WEP\n" +
                            "   VOIP               Infra   1     54 Mbit/s  20      ▂___  WEP\n" +
                            "   MARTINA            Infra   4     54 Mbit/s  32      ▂▄__  WPA2\n" +
                            "   N24PU1             Infra   7     11 Mbit/s  22      ▂___  --\n" +
                            "   alfa               Infra   1     54 Mbit/s  67      ▂▄▆_  WPA2\n" +
                            "   bertnet            Infra   5     54 Mbit/s  20      ▂___  WPA1";*/


                    TableRow tableRow = new TableRow(context);

                    allinf = allinf.replaceAll("\\s+", " ");
                    allinf = allinf.replaceFirst(" ", "");
                    String[] words = allinf.split(" ");
                    int num = 1;
                    String w = "";
                    for (String word : words) {

                        TextView text = new TextView(context);
                        text.setGravity(Gravity.CENTER_HORIZONTAL);
                        text.setTextColor(Color.parseColor("#000000"));
                        if (num == 1) {
                            if (Objects.equals(word, "*")) {
                                tableRow.setBackgroundColor(Color.parseColor("#19ff19"));
                                num--;
                            } else {
                                if (Objects.equals(word, "802.1X") || Objects.equals(word, "WPA2"))
                                {
                                    num--;
                                }
                                else
                                {
                                    text.setText(getSafeSubstring(word, 8));
                                    tableRow.addView(text);
                                }
                            }
                        } else {
                            if (num == 4) {
                                w = word;
                            } else {
                                if (num == 5) {
                                    w = w + word;
                                    text.setText(w);
                                    tableRow.addView(text);
                                } else {
                                    text.setText(word);
                                    tableRow.addView(text);
                                }
                            }


                        }

                        if (num == 8) {
                            table.addView(tableRow);
                            tableRow = new TableRow(context);
                            num = 0;
                        }
                        num++;
                    }
                }
                else
                {
                    info.setText("Соединения нет");
                }
            }
        });


    }

    private String getSafeSubstring(String s, int maxLength) {
        if(!TextUtils.isEmpty(s)){
        if(s.length() >= maxLength){
            return s.substring(0, maxLength);
        }
    }
        return s;
    }
}