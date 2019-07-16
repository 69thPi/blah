package com.example.tanmay.mk3;

import android.content.Intent;
import android.graphics.Color;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.MotionEvent;
import android.view.View;
import android.widget.Button;
import android.widget.LinearLayout;
import android.widget.ScrollView;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        ScrollView sView = (ScrollView)findViewById(R.id.sv);

        sView.setVerticalScrollBarEnabled(false);
        sView.setHorizontalScrollBarEnabled(false);
        final Button button = (Button) findViewById(R.id.button_id);
        final Button button1 = (Button) findViewById(R.id.b1);
        final Button button2= (Button) findViewById(R.id.b2);
        final Button button3 = (Button) findViewById(R.id.b3);
        final Button button4 = (Button) findViewById(R.id.b4);
        final Button button5 = (Button) findViewById(R.id.b5);
        final Button button6 = (Button) findViewById(R.id.b6);
        final Button button7 = (Button) findViewById(R.id.b7);

        button.setOnTouchListener(new View.OnTouchListener() {

            public boolean onTouch(View view, MotionEvent event) {
                if (event.getAction() == MotionEvent.ACTION_UP) {
                    button.setBackgroundColor(Color.RED);
                } else if (event.getAction() == MotionEvent.ACTION_DOWN) {
                    button.setBackgroundColor(Color.DKGRAY);
                }
                return false;
            }

        });
        button1.setOnTouchListener(new View.OnTouchListener() {
            public boolean onTouch(View view, MotionEvent event) {
                if (event.getAction() == MotionEvent.ACTION_UP) {
                     button2.setVisibility(View.VISIBLE);
                        button3.setVisibility(View.VISIBLE);
                        button4.setVisibility(View.VISIBLE);
                        button5.setVisibility(View.VISIBLE);
                        button6.setVisibility(View.VISIBLE);
                        button7.setVisibility(View.VISIBLE);
                } else if (event.getAction() == MotionEvent.ACTION_DOWN) {

                        button2.setVisibility(View.INVISIBLE);
                        button3.setVisibility(View.INVISIBLE);
                        button4.setVisibility(View.INVISIBLE);
                        button5.setVisibility(View.INVISIBLE);
                        button6.setVisibility(View.INVISIBLE);
                        button7.setVisibility(View.INVISIBLE);

                }
                return false;
            }

        });
        button2.setOnTouchListener(new View.OnTouchListener() {
            public boolean onTouch(View view, MotionEvent event) {
                if (event.getAction() == MotionEvent.ACTION_UP) {

                        button1.setVisibility(View.VISIBLE);
                        button3.setVisibility(View.VISIBLE);
                        button4.setVisibility(View.VISIBLE);
                        button5.setVisibility(View.VISIBLE);
                        button6.setVisibility(View.VISIBLE);
                        button7.setVisibility(View.VISIBLE);

                } else if (event.getAction() == MotionEvent.ACTION_DOWN) {

                        button1.setVisibility(View.INVISIBLE);
                        button3.setVisibility(View.INVISIBLE);
                        button4.setVisibility(View.INVISIBLE);
                        button5.setVisibility(View.INVISIBLE);
                        button6.setVisibility(View.INVISIBLE);
                        button7.setVisibility(View.INVISIBLE);

                }
                return false;
            }

        });
        button3.setOnTouchListener(new View.OnTouchListener() {
            public boolean onTouch(View view, MotionEvent event) {
                if (event.getAction() == MotionEvent.ACTION_UP) {

                        button1.setVisibility(View.VISIBLE);
                        button2.setVisibility(View.VISIBLE);
                        button4.setVisibility(View.VISIBLE);
                        button5.setVisibility(View.VISIBLE);
                        button6.setVisibility(View.VISIBLE);
                        button7.setVisibility(View.VISIBLE);

                } else if (event.getAction() == MotionEvent.ACTION_DOWN) {

                        button1.setVisibility(View.INVISIBLE);
                        button2.setVisibility(View.INVISIBLE);
                        button4.setVisibility(View.INVISIBLE);
                        button5.setVisibility(View.INVISIBLE);
                        button6.setVisibility(View.INVISIBLE);
                        button7.setVisibility(View.INVISIBLE);

                }
                return false;
            }

        });
        button4.setOnTouchListener(new View.OnTouchListener() {
            public boolean onTouch(View view, MotionEvent event) {
                if (event.getAction() == MotionEvent.ACTION_UP) {
                        button1.setVisibility(View.VISIBLE);
                        button2.setVisibility(View.VISIBLE);
                        button3.setVisibility(View.VISIBLE);
                        button5.setVisibility(View.VISIBLE);
                        button6.setVisibility(View.VISIBLE);
                        button7.setVisibility(View.VISIBLE);

                } else if (event.getAction() == MotionEvent.ACTION_DOWN) {

                        button1.setVisibility(View.INVISIBLE);
                        button2.setVisibility(View.INVISIBLE);
                        button3.setVisibility(View.INVISIBLE);
                        button5.setVisibility(View.INVISIBLE);
                        button6.setVisibility(View.INVISIBLE);
                        button7.setVisibility(View.INVISIBLE);

                }
                return false;
            }

        });
        button5.setOnTouchListener(new View.OnTouchListener() {
            public boolean onTouch(View view, MotionEvent event) {
                if (event.getAction() == MotionEvent.ACTION_UP) {

                        button1.setVisibility(View.VISIBLE);
                        button2.setVisibility(View.VISIBLE);
                        button3.setVisibility(View.VISIBLE);
                        button4.setVisibility(View.VISIBLE);
                        button6.setVisibility(View.VISIBLE);
                        button7.setVisibility(View.VISIBLE);

                } else if (event.getAction() == MotionEvent.ACTION_DOWN) {

                        button1.setVisibility(View.INVISIBLE);
                        button2.setVisibility(View.INVISIBLE);
                        button3.setVisibility(View.INVISIBLE);
                        button4.setVisibility(View.INVISIBLE);
                        button6.setVisibility(View.INVISIBLE);
                        button7.setVisibility(View.INVISIBLE);

                }
                return false;
            }

        });
        button6.setOnTouchListener(new View.OnTouchListener() {

            @Override
            public boolean onTouch(View view, MotionEvent event) {
                if (event.getAction() == MotionEvent.ACTION_UP) {

                        button1.setVisibility(View.VISIBLE);
                        button2.setVisibility(View.VISIBLE);
                        button3.setVisibility(View.VISIBLE);
                        button4.setVisibility(View.VISIBLE);
                        button5.setVisibility(View.VISIBLE);
                        button7.setVisibility(View.VISIBLE);

                } else if (event.getAction() == MotionEvent.ACTION_DOWN) {

                        button1.setVisibility(View.INVISIBLE);
                        button2.setVisibility(View.INVISIBLE);
                        button3.setVisibility(View.INVISIBLE);
                        button4.setVisibility(View.INVISIBLE);
                        button5.setVisibility(View.INVISIBLE);
                        button7.setVisibility(View.INVISIBLE);

                }
                return false;
            }

        });
        button7.setOnTouchListener(new View.OnTouchListener() {
             public boolean onTouch(View view, MotionEvent event) {
                if (event.getAction() == MotionEvent.ACTION_UP) {

                        button1.setVisibility(View.VISIBLE);
                        button2.setVisibility(View.VISIBLE);
                        button3.setVisibility(View.VISIBLE);
                        button4.setVisibility(View.VISIBLE);
                        button5.setVisibility(View.VISIBLE);
                        button6.setVisibility(View.VISIBLE);

                } else if (event.getAction() == MotionEvent.ACTION_DOWN) {

                        button1.setVisibility(View.INVISIBLE);
                        button2.setVisibility(View.INVISIBLE);
                        button3.setVisibility(View.INVISIBLE);
                        button4.setVisibility(View.INVISIBLE);
                        button5.setVisibility(View.INVISIBLE);
                        button6.setVisibility(View.INVISIBLE);

                }
                return false;
            }

        });

    }
    public void new_win(View view)
    {

        Intent intent=new Intent(this,Main2Activity.class);
        startActivity(intent);
        setContentView(R.id.activity_main2);

    }

}

