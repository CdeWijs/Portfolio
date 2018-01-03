using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Collectible : MonoBehaviour
{
    public GameObject collectiblePref;

    private GameObject collectible;
    private GameObject[] spawnArray;
    private GameObject currentSpawner;
    private AudioSource audioSource;
    private int index;

    private void Start()
    {
        spawnArray = GameObject.FindGameObjectsWithTag("Spawner");
        audioSource = GetComponent<AudioSource>();
        InstantiateObject();
    }

    void InstantiateObject ()
    {
        index = Random.Range(0, spawnArray.Length);
        currentSpawner = spawnArray[index];
        collectible = Instantiate(collectiblePref, currentSpawner.transform) as GameObject;
    }

    public void PickUp()
    {
        audioSource.Play();
        Destroy(collectible);
        Score.score++;
        InstantiateObject();
    }
}
