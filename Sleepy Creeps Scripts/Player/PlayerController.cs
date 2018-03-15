using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerController : MonoBehaviour
{
    // Declare in inspector
    public LevelManager levelManager;
    public Score scoreScript;
    public float horizontalSpeed = 150.0f;
    public float verticalSpeed = 3.0f;
    public GameObject sphereTrigger;
    public AudioClip clipDeath;

    private AutoIntensity autoIntensity;
    private Rigidbody rigidBody;
    private AudioSource audioSource;
    private bool freezeControls = false;
    private bool playedDeath = false;

    private void Start()
    {
        autoIntensity = FindObjectOfType<AutoIntensity>();
        rigidBody = GetComponent<Rigidbody>();
        rigidBody.freezeRotation = true;
        audioSource = GetComponent<AudioSource>();
    }


    void Update()
    {
        float x = Input.GetAxis("Horizontal") * Time.deltaTime * horizontalSpeed;
        float z = Input.GetAxis("Vertical") * Time.deltaTime * verticalSpeed;

        if (!freezeControls)
        {
            transform.Rotate(0, x, 0);
            transform.Translate(0, 0, z);
        }

        if (autoIntensity.dot <= 0)
        {
            sphereTrigger.SetActive(true);
        }
        else
        {
            sphereTrigger.SetActive(false);
        }
    }

    public void PlayerDeath()
    {
        if (!playedDeath)
        {
            audioSource.clip = clipDeath;
            audioSource.Play();
            playedDeath = true;
        }

        scoreScript.SetHighScore();
        freezeControls = true;
        Invoke("GameOver", 5f);
    }

    private void GameOver()
    {
        levelManager.LoadLevel("Lose");
    }
}
