using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SetSunLight : MonoBehaviour
{
    public Transform stars;

    private Material sky;

    void Start () {
        sky = RenderSettings.skybox;
	}

	void Update () {
        stars.transform.rotation = transform.rotation;
	}
}
