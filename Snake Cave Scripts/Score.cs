using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Score : MonoBehaviour
{
    public static int score;

    private Text text;

    private void Start()
    {
        text = GetComponent<Text>();
        score = 0;
    }

    private void Update()
    {
        text.text = score.ToString();
    }

    public void SetHighScore()
    {
        PlayerPrefsManager.SetHighScore(score);
    }
}
