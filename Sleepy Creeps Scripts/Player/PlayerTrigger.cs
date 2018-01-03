using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerTrigger : MonoBehaviour {

    private PlayerController playerController;
    
	void Start () {
        playerController = FindObjectOfType<PlayerController>();
	}

    private void OnTriggerEnter(Collider other)
    {
        if (other.CompareTag("Enemy"))
        {
            playerController.PlayerDeath();
        }
    }
}
